#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct viafb_dev {scalar_t__ chip_type; int fbmem_len; int /*<<< orphan*/ * engine_mmio; int /*<<< orphan*/ * fbmem; void* fbmem_start; TYPE_1__* pdev; int /*<<< orphan*/  engine_len; void* engine_start; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ UNICHROME_VX900 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ioremap_nocache (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ioremap_wc (void*,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_resource_len (TYPE_1__*,int) ; 
 void* pci_resource_start (TYPE_1__*,int) ; 
 int viafb_get_fb_size_from_pci (scalar_t__) ; 

__attribute__((used)) static int via_pci_setup_mmio(struct viafb_dev *vdev)
{
	int ret;
	/*
	 * Hook up to the device registers.  Note that we soldier
	 * on if it fails; the framebuffer can operate (without
	 * acceleration) without this region.
	 */
	vdev->engine_start = pci_resource_start(vdev->pdev, 1);
	vdev->engine_len = pci_resource_len(vdev->pdev, 1);
	vdev->engine_mmio = ioremap_nocache(vdev->engine_start,
			vdev->engine_len);
	if (vdev->engine_mmio == NULL)
		dev_err(&vdev->pdev->dev,
				"Unable to map engine MMIO; operation will be "
				"slow and crippled.\n");
	/*
	 * Map in framebuffer memory.  For now, failure here is
	 * fatal.  Unfortunately, in the absence of significant
	 * vmalloc space, failure here is also entirely plausible.
	 * Eventually we want to move away from mapping this
	 * entire region.
	 */
	if (vdev->chip_type == UNICHROME_VX900)
		vdev->fbmem_start = pci_resource_start(vdev->pdev, 2);
	else
		vdev->fbmem_start = pci_resource_start(vdev->pdev, 0);
	ret = vdev->fbmem_len = viafb_get_fb_size_from_pci(vdev->chip_type);
	if (ret < 0)
		goto out_unmap;

	/* try to map less memory on failure, 8 MB should be still enough */
	for (; vdev->fbmem_len >= 8 << 20; vdev->fbmem_len /= 2) {
		vdev->fbmem = ioremap_wc(vdev->fbmem_start, vdev->fbmem_len);
		if (vdev->fbmem)
			break;
	}

	if (vdev->fbmem == NULL) {
		ret = -ENOMEM;
		goto out_unmap;
	}
	return 0;
out_unmap:
	iounmap(vdev->engine_mmio);
	return ret;
}