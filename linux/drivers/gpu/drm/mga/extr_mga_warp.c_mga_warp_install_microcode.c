#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ihex_binrec {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct firmware {scalar_t__ data; } ;
struct TYPE_5__ {int chipset; unsigned long* warp_pipe_phys; TYPE_1__* warp; } ;
typedef  TYPE_2__ drm_mga_private_t ;
struct TYPE_4__ {unsigned char* handle; unsigned long offset; unsigned int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,unsigned long,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int ENOMEM ; 
 char* FIRMWARE_G200 ; 
 char* FIRMWARE_G400 ; 
 scalar_t__ IS_ERR (struct platform_device*) ; 
#define  MGA_CARD_TYPE_G200 130 
#define  MGA_CARD_TYPE_G400 129 
#define  MGA_CARD_TYPE_G550 128 
 int MGA_MAX_G200_PIPES ; 
 int MGA_MAX_G400_PIPES ; 
 unsigned int PAGE_ALIGN (unsigned int) ; 
 int PTR_ERR (struct platform_device*) ; 
 unsigned int WARP_UCODE_SIZE (unsigned int) ; 
 unsigned int be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct ihex_binrec* ihex_next_binrec (struct ihex_binrec const*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (unsigned long*,int /*<<< orphan*/ ,int) ; 
 struct platform_device* platform_device_register_simple (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_ihex_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 

int mga_warp_install_microcode(drm_mga_private_t *dev_priv)
{
	unsigned char *vcbase = dev_priv->warp->handle;
	unsigned long pcbase = dev_priv->warp->offset;
	const char *firmware_name;
	struct platform_device *pdev;
	const struct firmware *fw = NULL;
	const struct ihex_binrec *rec;
	unsigned int size;
	int n_pipes, where;
	int rc = 0;

	switch (dev_priv->chipset) {
	case MGA_CARD_TYPE_G400:
	case MGA_CARD_TYPE_G550:
		firmware_name = FIRMWARE_G400;
		n_pipes = MGA_MAX_G400_PIPES;
		break;
	case MGA_CARD_TYPE_G200:
		firmware_name = FIRMWARE_G200;
		n_pipes = MGA_MAX_G200_PIPES;
		break;
	default:
		return -EINVAL;
	}

	pdev = platform_device_register_simple("mga_warp", 0, NULL, 0);
	if (IS_ERR(pdev)) {
		DRM_ERROR("mga: Failed to register microcode\n");
		return PTR_ERR(pdev);
	}
	rc = request_ihex_firmware(&fw, firmware_name, &pdev->dev);
	platform_device_unregister(pdev);
	if (rc) {
		DRM_ERROR("mga: Failed to load microcode \"%s\"\n",
			  firmware_name);
		return rc;
	}

	size = 0;
	where = 0;
	for (rec = (const struct ihex_binrec *)fw->data;
	     rec;
	     rec = ihex_next_binrec(rec)) {
		size += WARP_UCODE_SIZE(be16_to_cpu(rec->len));
		where++;
	}

	if (where != n_pipes) {
		DRM_ERROR("mga: Invalid microcode \"%s\"\n", firmware_name);
		rc = -EINVAL;
		goto out;
	}
	size = PAGE_ALIGN(size);
	DRM_DEBUG("MGA ucode size = %d bytes\n", size);
	if (size > dev_priv->warp->size) {
		DRM_ERROR("microcode too large! (%u > %lu)\n",
			  size, dev_priv->warp->size);
		rc = -ENOMEM;
		goto out;
	}

	memset(dev_priv->warp_pipe_phys, 0, sizeof(dev_priv->warp_pipe_phys));

	where = 0;
	for (rec = (const struct ihex_binrec *)fw->data;
	     rec;
	     rec = ihex_next_binrec(rec)) {
		unsigned int src_size, dst_size;

		DRM_DEBUG(" pcbase = 0x%08lx  vcbase = %p\n", pcbase, vcbase);
		dev_priv->warp_pipe_phys[where] = pcbase;
		src_size = be16_to_cpu(rec->len);
		dst_size = WARP_UCODE_SIZE(src_size);
		memcpy(vcbase, rec->data, src_size);
		pcbase += dst_size;
		vcbase += dst_size;
		where++;
	}

out:
	release_firmware(fw);
	return rc;
}