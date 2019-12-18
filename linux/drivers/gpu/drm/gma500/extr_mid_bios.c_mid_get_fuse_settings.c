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
typedef  int uint32_t ;
struct pci_dev {int dummy; } ;
struct drm_psb_private {int iLVDS_enable; int is_lvds_on; int is_mipi_on; int video_device_fuse; int fuse_reg_value; int core_freq; } ;
struct drm_device {int /*<<< orphan*/  dev; TYPE_1__* pdev; struct drm_psb_private* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,char*) ; 
 int FB_MIPI_DISABLE ; 
 int /*<<< orphan*/  FB_REG06 ; 
 int /*<<< orphan*/  FB_REG09 ; 
#define  FB_SKU_100 130 
#define  FB_SKU_100L 129 
#define  FB_SKU_83 128 
 int FB_SKU_MASK ; 
 int FB_SKU_SHIFT ; 
 scalar_t__ IS_MRST (struct drm_device*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_domain_nr (int /*<<< orphan*/ ) ; 
 struct pci_dev* pci_get_domain_bus_and_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mid_get_fuse_settings(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct pci_dev *pci_root =
		pci_get_domain_bus_and_slot(pci_domain_nr(dev->pdev->bus),
					    0, 0);
	uint32_t fuse_value = 0;
	uint32_t fuse_value_tmp = 0;

#define FB_REG06 0xD0810600
#define FB_MIPI_DISABLE  (1 << 11)
#define FB_REG09 0xD0810900
#define FB_SKU_MASK  0x7000
#define FB_SKU_SHIFT 12
#define FB_SKU_100 0
#define FB_SKU_100L 1
#define FB_SKU_83 2
	if (pci_root == NULL) {
		WARN_ON(1);
		return;
	}


	pci_write_config_dword(pci_root, 0xD0, FB_REG06);
	pci_read_config_dword(pci_root, 0xD4, &fuse_value);

	/* FB_MIPI_DISABLE doesn't mean LVDS on with Medfield */
	if (IS_MRST(dev))
		dev_priv->iLVDS_enable = fuse_value & FB_MIPI_DISABLE;

	DRM_INFO("internal display is %s\n",
		 dev_priv->iLVDS_enable ? "LVDS display" : "MIPI display");

	 /* Prevent runtime suspend at start*/
	 if (dev_priv->iLVDS_enable) {
		dev_priv->is_lvds_on = true;
		dev_priv->is_mipi_on = false;
	} else {
		dev_priv->is_mipi_on = true;
		dev_priv->is_lvds_on = false;
	}

	dev_priv->video_device_fuse = fuse_value;

	pci_write_config_dword(pci_root, 0xD0, FB_REG09);
	pci_read_config_dword(pci_root, 0xD4, &fuse_value);

	dev_dbg(dev->dev, "SKU values is 0x%x.\n", fuse_value);
	fuse_value_tmp = (fuse_value & FB_SKU_MASK) >> FB_SKU_SHIFT;

	dev_priv->fuse_reg_value = fuse_value;

	switch (fuse_value_tmp) {
	case FB_SKU_100:
		dev_priv->core_freq = 200;
		break;
	case FB_SKU_100L:
		dev_priv->core_freq = 100;
		break;
	case FB_SKU_83:
		dev_priv->core_freq = 166;
		break;
	default:
		dev_warn(dev->dev, "Invalid SKU values, SKU value = 0x%08x\n",
								fuse_value_tmp);
		dev_priv->core_freq = 0;
	}
	dev_dbg(dev->dev, "LNC core clk is %dMHz.\n", dev_priv->core_freq);
	pci_dev_put(pci_root);
}