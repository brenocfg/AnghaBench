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
struct i40e_vf {int /*<<< orphan*/  vf_states; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_VF_STATE_ACTIVE ; 
 int /*<<< orphan*/  i40e_reset_vf (struct i40e_vf*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i40e_vc_reset_vf_msg(struct i40e_vf *vf)
{
	if (test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states))
		i40e_reset_vf(vf, false);
}