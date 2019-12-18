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
struct ice_vf {int /*<<< orphan*/  vf_states; } ;
struct ice_pf {int num_alloc_vfs; struct ice_vf* vf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_VF_STATE_ACTIVE ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ice_active_vfs(struct ice_pf *pf)
{
	struct ice_vf *vf = pf->vf;
	int i;

	for (i = 0; i < pf->num_alloc_vfs; i++, vf++)
		if (test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states))
			return true;
	return false;
}