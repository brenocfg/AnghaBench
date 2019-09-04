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
typedef  int /*<<< orphan*/  u32 ;
struct mem_ctl_info {struct i7300_pvt* pvt_info; } ;
struct i7300_pvt {int /*<<< orphan*/  pci_dev_16_1_fsb_addr_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMASK_FBD ; 
 int /*<<< orphan*/  EMASK_FBD_ERR_MASK ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i7300_enable_error_reporting(struct mem_ctl_info *mci)
{
	struct i7300_pvt *pvt = mci->pvt_info;
	u32 fbd_error_mask;

	/* Read the FBD Error Mask Register */
	pci_read_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
			      EMASK_FBD, &fbd_error_mask);

	/* Enable with a '0' */
	fbd_error_mask &= ~(EMASK_FBD_ERR_MASK);

	pci_write_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
			       EMASK_FBD, fbd_error_mask);
}