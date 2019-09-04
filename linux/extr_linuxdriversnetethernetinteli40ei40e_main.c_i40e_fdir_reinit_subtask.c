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
struct i40e_pf {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __I40E_DOWN ; 
 int /*<<< orphan*/  __I40E_FD_FLUSH_REQUESTED ; 
 int /*<<< orphan*/  i40e_fdir_check_and_reenable (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_fdir_flush_and_replay (struct i40e_pf*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_fdir_reinit_subtask(struct i40e_pf *pf)
{

	/* if interface is down do nothing */
	if (test_bit(__I40E_DOWN, pf->state))
		return;

	if (test_bit(__I40E_FD_FLUSH_REQUESTED, pf->state))
		i40e_fdir_flush_and_replay(pf);

	i40e_fdir_check_and_reenable(pf);

}