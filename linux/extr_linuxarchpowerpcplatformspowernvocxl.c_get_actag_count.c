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
typedef  int u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ACTAG_MASK ; 
 int ESRCH ; 
 scalar_t__ OCXL_DVSEC_AFU_CTRL_ACTAG_SUP ; 
 int find_dvsec_afu_ctrl (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 

__attribute__((used)) static int get_actag_count(struct pci_dev *dev, int afu_idx, int *actag)
{
	int pos;
	u16 actag_sup;

	pos = find_dvsec_afu_ctrl(dev, afu_idx);
	if (!pos)
		return -ESRCH;

	pci_read_config_word(dev, pos + OCXL_DVSEC_AFU_CTRL_ACTAG_SUP,
			&actag_sup);
	*actag = actag_sup & ACTAG_MASK;
	return 0;
}