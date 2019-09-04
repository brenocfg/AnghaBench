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
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct cxl {int user_image_loaded; int perst_select_user; int perst_loads_image; int slices; int ps_size; int user_irqs; TYPE_1__* native; int /*<<< orphan*/  base_image; int /*<<< orphan*/  caia_minor; int /*<<< orphan*/  caia_major; int /*<<< orphan*/  psl_rev; int /*<<< orphan*/  vsec_status; } ;
struct TYPE_2__ {int ps_off; int afu_desc_off; int afu_desc_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_READ_VSEC_AFU_DESC_OFF (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  CXL_READ_VSEC_AFU_DESC_SIZE (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  CXL_READ_VSEC_BASE_IMAGE (struct pci_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CXL_READ_VSEC_CAIA_MAJOR (struct pci_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CXL_READ_VSEC_CAIA_MINOR (struct pci_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CXL_READ_VSEC_IMAGE_STATE (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  CXL_READ_VSEC_LENGTH (struct pci_dev*,int,scalar_t__*) ; 
 int /*<<< orphan*/  CXL_READ_VSEC_NAFUS (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  CXL_READ_VSEC_PSL_REVISION (struct pci_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CXL_READ_VSEC_PS_OFF (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  CXL_READ_VSEC_PS_SIZE (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  CXL_READ_VSEC_STATUS (struct pci_dev*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ CXL_VSEC_MIN_SIZE ; 
 int CXL_VSEC_PERST_LOADS_IMAGE ; 
 int CXL_VSEC_USER_IMAGE_LOADED ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int find_cxl_vsec (struct pci_dev*) ; 
 int pnv_cxl_get_irq_count (struct pci_dev*) ; 

__attribute__((used)) static int cxl_read_vsec(struct cxl *adapter, struct pci_dev *dev)
{
	int vsec;
	u32 afu_desc_off, afu_desc_size;
	u32 ps_off, ps_size;
	u16 vseclen;
	u8 image_state;

	if (!(vsec = find_cxl_vsec(dev))) {
		dev_err(&dev->dev, "ABORTING: CXL VSEC not found!\n");
		return -ENODEV;
	}

	CXL_READ_VSEC_LENGTH(dev, vsec, &vseclen);
	if (vseclen < CXL_VSEC_MIN_SIZE) {
		dev_err(&dev->dev, "ABORTING: CXL VSEC too short\n");
		return -EINVAL;
	}

	CXL_READ_VSEC_STATUS(dev, vsec, &adapter->vsec_status);
	CXL_READ_VSEC_PSL_REVISION(dev, vsec, &adapter->psl_rev);
	CXL_READ_VSEC_CAIA_MAJOR(dev, vsec, &adapter->caia_major);
	CXL_READ_VSEC_CAIA_MINOR(dev, vsec, &adapter->caia_minor);
	CXL_READ_VSEC_BASE_IMAGE(dev, vsec, &adapter->base_image);
	CXL_READ_VSEC_IMAGE_STATE(dev, vsec, &image_state);
	adapter->user_image_loaded = !!(image_state & CXL_VSEC_USER_IMAGE_LOADED);
	adapter->perst_select_user = !!(image_state & CXL_VSEC_USER_IMAGE_LOADED);
	adapter->perst_loads_image = !!(image_state & CXL_VSEC_PERST_LOADS_IMAGE);

	CXL_READ_VSEC_NAFUS(dev, vsec, &adapter->slices);
	CXL_READ_VSEC_AFU_DESC_OFF(dev, vsec, &afu_desc_off);
	CXL_READ_VSEC_AFU_DESC_SIZE(dev, vsec, &afu_desc_size);
	CXL_READ_VSEC_PS_OFF(dev, vsec, &ps_off);
	CXL_READ_VSEC_PS_SIZE(dev, vsec, &ps_size);

	/* Convert everything to bytes, because there is NO WAY I'd look at the
	 * code a month later and forget what units these are in ;-) */
	adapter->native->ps_off = ps_off * 64 * 1024;
	adapter->ps_size = ps_size * 64 * 1024;
	adapter->native->afu_desc_off = afu_desc_off * 64 * 1024;
	adapter->native->afu_desc_size = afu_desc_size * 64 * 1024;

	/* Total IRQs - 1 PSL ERROR - #AFU*(1 slice error + 1 DSI) */
	adapter->user_irqs = pnv_cxl_get_irq_count(dev) - 1 - 2*adapter->slices;

	return 0;
}