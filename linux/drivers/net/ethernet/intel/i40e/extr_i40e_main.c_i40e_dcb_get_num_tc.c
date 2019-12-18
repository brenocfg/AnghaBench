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
struct TYPE_2__ {int* prioritytable; } ;
struct i40e_dcbx_config {TYPE_1__ etscfg; } ;

/* Variables and functions */
 int BIT (int) ; 
 int I40E_MAX_TRAFFIC_CLASS ; 
 int I40E_MAX_USER_PRIORITY ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static u8 i40e_dcb_get_num_tc(struct i40e_dcbx_config *dcbcfg)
{
	int i, tc_unused = 0;
	u8 num_tc = 0;
	u8 ret = 0;

	/* Scan the ETS Config Priority Table to find
	 * traffic class enabled for a given priority
	 * and create a bitmask of enabled TCs
	 */
	for (i = 0; i < I40E_MAX_USER_PRIORITY; i++)
		num_tc |= BIT(dcbcfg->etscfg.prioritytable[i]);

	/* Now scan the bitmask to check for
	 * contiguous TCs starting with TC0
	 */
	for (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) {
		if (num_tc & BIT(i)) {
			if (!tc_unused) {
				ret++;
			} else {
				pr_err("Non-contiguous TC - Disabling DCB\n");
				return 1;
			}
		} else {
			tc_unused = 1;
		}
	}

	/* There is always at least TC0 */
	if (!ret)
		ret = 1;

	return ret;
}