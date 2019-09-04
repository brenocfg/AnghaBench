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
struct i40e_pf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_rebuild (struct i40e_pf*,int,int) ; 
 int i40e_reset (struct i40e_pf*) ; 

__attribute__((used)) static void i40e_reset_and_rebuild(struct i40e_pf *pf, bool reinit,
				   bool lock_acquired)
{
	int ret;
	/* Now we wait for GRST to settle out.
	 * We don't have to delete the VEBs or VSIs from the hw switch
	 * because the reset will make them disappear.
	 */
	ret = i40e_reset(pf);
	if (!ret)
		i40e_rebuild(pf, reinit, lock_acquired);
}