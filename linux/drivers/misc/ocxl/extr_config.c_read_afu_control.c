#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ocxl_afu_config {int dvsec_afu_control_pos; void* actag_supported; void* pasid_supported_log; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int ENODEV ; 
 void* EXTRACT_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ OCXL_DVSEC_AFU_CTRL_ACTAG_SUP ; 
 scalar_t__ OCXL_DVSEC_AFU_CTRL_PASID_SUP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int find_dvsec_afu_ctrl (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_afu_control(struct pci_dev *dev, struct ocxl_afu_config *afu)
{
	int pos;
	u8 val8;
	u16 val16;

	pos = find_dvsec_afu_ctrl(dev, afu->idx);
	if (!pos) {
		dev_err(&dev->dev, "Can't find AFU control DVSEC for AFU %d\n",
			afu->idx);
		return -ENODEV;
	}
	afu->dvsec_afu_control_pos = pos;

	pci_read_config_byte(dev, pos + OCXL_DVSEC_AFU_CTRL_PASID_SUP, &val8);
	afu->pasid_supported_log = EXTRACT_BITS(val8, 0, 4);

	pci_read_config_word(dev, pos + OCXL_DVSEC_AFU_CTRL_ACTAG_SUP, &val16);
	afu->actag_supported = EXTRACT_BITS(val16, 0, 11);
	return 0;
}