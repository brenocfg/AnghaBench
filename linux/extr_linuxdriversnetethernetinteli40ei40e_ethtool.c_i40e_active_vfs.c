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
struct i40e_pf {int num_alloc_vfs; struct i40e_vf* vf; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_VF_STATE_ACTIVE ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool i40e_active_vfs(struct i40e_pf *pf)
{
	struct i40e_vf *vfs = pf->vf;
	int i;

	for (i = 0; i < pf->num_alloc_vfs; i++)
		if (test_bit(I40E_VF_STATE_ACTIVE, &vfs[i].vf_states))
			return true;
	return false;
}