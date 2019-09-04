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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int AFU_INDEX_MASK ; 
 int AFU_INDEX_SHIFT ; 
 int AFU_PRESENT ; 
 int ESRCH ; 
 int /*<<< orphan*/  OCXL_DVSEC_FUNC_ID ; 
 scalar_t__ OCXL_DVSEC_FUNC_OFF_INDEX ; 
 int find_dvsec_from_pos (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 

__attribute__((used)) static int get_max_afu_index(struct pci_dev *dev, int *afu_idx)
{
	int pos;
	u32 val;

	pos = find_dvsec_from_pos(dev, OCXL_DVSEC_FUNC_ID, 0);
	if (!pos)
		return -ESRCH;

	pci_read_config_dword(dev, pos + OCXL_DVSEC_FUNC_OFF_INDEX, &val);
	if (val & AFU_PRESENT)
		*afu_idx = (val & AFU_INDEX_MASK) >> AFU_INDEX_SHIFT;
	else
		*afu_idx = -1;
	return 0;
}