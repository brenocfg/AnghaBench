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
struct i40e_vsi {struct i40e_pf* back; } ;
struct i40e_pf {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __I40E_CONFIG_BUSY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_down (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_up (struct i40e_vsi*) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void i40e_vsi_reinit_locked(struct i40e_vsi *vsi)
{
	struct i40e_pf *pf = vsi->back;

	WARN_ON(in_interrupt());
	while (test_and_set_bit(__I40E_CONFIG_BUSY, pf->state))
		usleep_range(1000, 2000);
	i40e_down(vsi);

	i40e_up(vsi);
	clear_bit(__I40E_CONFIG_BUSY, pf->state);
}