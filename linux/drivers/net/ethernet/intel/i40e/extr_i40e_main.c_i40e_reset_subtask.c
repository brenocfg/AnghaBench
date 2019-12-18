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
struct i40e_pf {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __I40E_CONFIG_BUSY ; 
 int /*<<< orphan*/  __I40E_CORE_RESET_REQUESTED ; 
 int /*<<< orphan*/  __I40E_DOWN ; 
 int /*<<< orphan*/  __I40E_DOWN_REQUESTED ; 
 int /*<<< orphan*/  __I40E_GLOBAL_RESET_REQUESTED ; 
 int /*<<< orphan*/  __I40E_PF_RESET_REQUESTED ; 
 int /*<<< orphan*/  __I40E_REINIT_REQUESTED ; 
 int /*<<< orphan*/  __I40E_RESET_INTR_RECEIVED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_do_reset (struct i40e_pf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i40e_prep_for_reset (struct i40e_pf*,int) ; 
 int /*<<< orphan*/  i40e_rebuild (struct i40e_pf*,int,int) ; 
 int /*<<< orphan*/  i40e_reset (struct i40e_pf*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_reset_subtask(struct i40e_pf *pf)
{
	u32 reset_flags = 0;

	if (test_bit(__I40E_REINIT_REQUESTED, pf->state)) {
		reset_flags |= BIT(__I40E_REINIT_REQUESTED);
		clear_bit(__I40E_REINIT_REQUESTED, pf->state);
	}
	if (test_bit(__I40E_PF_RESET_REQUESTED, pf->state)) {
		reset_flags |= BIT(__I40E_PF_RESET_REQUESTED);
		clear_bit(__I40E_PF_RESET_REQUESTED, pf->state);
	}
	if (test_bit(__I40E_CORE_RESET_REQUESTED, pf->state)) {
		reset_flags |= BIT(__I40E_CORE_RESET_REQUESTED);
		clear_bit(__I40E_CORE_RESET_REQUESTED, pf->state);
	}
	if (test_bit(__I40E_GLOBAL_RESET_REQUESTED, pf->state)) {
		reset_flags |= BIT(__I40E_GLOBAL_RESET_REQUESTED);
		clear_bit(__I40E_GLOBAL_RESET_REQUESTED, pf->state);
	}
	if (test_bit(__I40E_DOWN_REQUESTED, pf->state)) {
		reset_flags |= BIT(__I40E_DOWN_REQUESTED);
		clear_bit(__I40E_DOWN_REQUESTED, pf->state);
	}

	/* If there's a recovery already waiting, it takes
	 * precedence before starting a new reset sequence.
	 */
	if (test_bit(__I40E_RESET_INTR_RECEIVED, pf->state)) {
		i40e_prep_for_reset(pf, false);
		i40e_reset(pf);
		i40e_rebuild(pf, false, false);
	}

	/* If we're already down or resetting, just bail */
	if (reset_flags &&
	    !test_bit(__I40E_DOWN, pf->state) &&
	    !test_bit(__I40E_CONFIG_BUSY, pf->state)) {
		i40e_do_reset(pf, reset_flags, false);
	}
}