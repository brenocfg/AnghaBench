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
typedef  int u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EBUSY ; 
 scalar_t__ EXTRACT_BIT (int,int) ; 
 unsigned long HZ ; 
 unsigned long OCXL_CFG_TIMEOUT ; 
 scalar_t__ OCXL_DVSEC_AFU_CTRL_TERM_PASID ; 
 int OCXL_DVSEC_PASID_MASK ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

int ocxl_config_terminate_pasid(struct pci_dev *dev, int afu_control, int pasid)
{
	u32 val;
	unsigned long timeout;

	pci_read_config_dword(dev, afu_control + OCXL_DVSEC_AFU_CTRL_TERM_PASID,
			&val);
	if (EXTRACT_BIT(val, 20)) {
		dev_err(&dev->dev,
			"Can't terminate PASID %#x, previous termination didn't complete\n",
			pasid);
		return -EBUSY;
	}

	val &= ~OCXL_DVSEC_PASID_MASK;
	val |= pasid & OCXL_DVSEC_PASID_MASK;
	val |= BIT(20);
	pci_write_config_dword(dev,
			afu_control + OCXL_DVSEC_AFU_CTRL_TERM_PASID,
			val);

	timeout = jiffies + (HZ * OCXL_CFG_TIMEOUT);
	pci_read_config_dword(dev, afu_control + OCXL_DVSEC_AFU_CTRL_TERM_PASID,
			&val);
	while (EXTRACT_BIT(val, 20)) {
		if (time_after_eq(jiffies, timeout)) {
			dev_err(&dev->dev,
				"Timeout while waiting for AFU to terminate PASID %#x\n",
				pasid);
			return -EBUSY;
		}
		cpu_relax();
		pci_read_config_dword(dev,
				afu_control + OCXL_DVSEC_AFU_CTRL_TERM_PASID,
				&val);
	}
	return 0;
}