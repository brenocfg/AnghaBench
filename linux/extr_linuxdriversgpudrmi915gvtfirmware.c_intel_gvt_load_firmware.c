#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int vendor; int device; int revision; int /*<<< orphan*/  dev; } ;
struct intel_gvt_firmware {char* cfg_space; char* mmio; int firmware_loaded; } ;
struct intel_gvt_device_info {int /*<<< orphan*/  mmio_size; int /*<<< orphan*/  cfg_space_size; } ;
struct intel_gvt {struct intel_gvt_firmware firmware; struct drm_i915_private* dev_priv; struct intel_gvt_device_info device_info; } ;
struct gvt_firmware_header {int /*<<< orphan*/  mmio_size; scalar_t__ mmio_offset; int /*<<< orphan*/  cfg_space_size; scalar_t__ cfg_space_offset; } ;
struct firmware {scalar_t__ data; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* GVT_FIRMWARE_PATH ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  expose_firmware_sysfs (struct intel_gvt*) ; 
 int /*<<< orphan*/  gvt_dbg_core (char*,...) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int,int,int) ; 
 int verify_firmware (struct intel_gvt*,struct firmware const*) ; 

int intel_gvt_load_firmware(struct intel_gvt *gvt)
{
	struct intel_gvt_device_info *info = &gvt->device_info;
	struct drm_i915_private *dev_priv = gvt->dev_priv;
	struct pci_dev *pdev = dev_priv->drm.pdev;
	struct intel_gvt_firmware *firmware = &gvt->firmware;
	struct gvt_firmware_header *h;
	const struct firmware *fw;
	char *path;
	void *mem;
	int ret;

	path = kmalloc(PATH_MAX, GFP_KERNEL);
	if (!path)
		return -ENOMEM;

	mem = kmalloc(info->cfg_space_size, GFP_KERNEL);
	if (!mem) {
		kfree(path);
		return -ENOMEM;
	}

	firmware->cfg_space = mem;

	mem = kmalloc(info->mmio_size, GFP_KERNEL);
	if (!mem) {
		kfree(path);
		kfree(firmware->cfg_space);
		return -ENOMEM;
	}

	firmware->mmio = mem;

	sprintf(path, "%s/vid_0x%04x_did_0x%04x_rid_0x%02x.golden_hw_state",
		 GVT_FIRMWARE_PATH, pdev->vendor, pdev->device,
		 pdev->revision);

	gvt_dbg_core("request hw state firmware %s...\n", path);

	ret = request_firmware(&fw, path, &dev_priv->drm.pdev->dev);
	kfree(path);

	if (ret)
		goto expose_firmware;

	gvt_dbg_core("success.\n");

	ret = verify_firmware(gvt, fw);
	if (ret)
		goto out_free_fw;

	gvt_dbg_core("verified.\n");

	h = (struct gvt_firmware_header *)fw->data;

	memcpy(firmware->cfg_space, fw->data + h->cfg_space_offset,
	       h->cfg_space_size);
	memcpy(firmware->mmio, fw->data + h->mmio_offset,
	       h->mmio_size);

	release_firmware(fw);
	firmware->firmware_loaded = true;
	return 0;

out_free_fw:
	release_firmware(fw);
expose_firmware:
	expose_firmware_sysfs(gvt);
	return 0;
}