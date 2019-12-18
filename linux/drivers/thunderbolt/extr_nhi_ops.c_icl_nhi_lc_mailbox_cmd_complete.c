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
struct tb_nhi {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  VS_CAP_18 ; 
 int VS_CAP_18_DONE ; 
 int /*<<< orphan*/  VS_CAP_19 ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int icl_nhi_lc_mailbox_cmd_complete(struct tb_nhi *nhi, int timeout)
{
	unsigned long end;
	u32 data;

	if (!timeout)
		goto clear;

	end = jiffies + msecs_to_jiffies(timeout);
	do {
		pci_read_config_dword(nhi->pdev, VS_CAP_18, &data);
		if (data & VS_CAP_18_DONE)
			goto clear;
		msleep(100);
	} while (time_before(jiffies, end));

	return -ETIMEDOUT;

clear:
	/* Clear the valid bit */
	pci_write_config_dword(nhi->pdev, VS_CAP_19, 0);
	return 0;
}