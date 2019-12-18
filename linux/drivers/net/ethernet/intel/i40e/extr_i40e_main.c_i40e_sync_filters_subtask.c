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
struct i40e_pf {int num_alloc_vsi; int /*<<< orphan*/  state; TYPE_1__** vsi; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int I40E_VSI_FLAG_FILTER_CHANGED ; 
 int /*<<< orphan*/  __I40E_MACVLAN_SYNC_PENDING ; 
 int /*<<< orphan*/  __I40E_VF_DISABLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i40e_sync_vsi_filters (TYPE_1__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_sync_filters_subtask(struct i40e_pf *pf)
{
	int v;

	if (!pf)
		return;
	if (!test_and_clear_bit(__I40E_MACVLAN_SYNC_PENDING, pf->state))
		return;
	if (test_and_set_bit(__I40E_VF_DISABLE, pf->state)) {
		set_bit(__I40E_MACVLAN_SYNC_PENDING, pf->state);
		return;
	}

	for (v = 0; v < pf->num_alloc_vsi; v++) {
		if (pf->vsi[v] &&
		    (pf->vsi[v]->flags & I40E_VSI_FLAG_FILTER_CHANGED)) {
			int ret = i40e_sync_vsi_filters(pf->vsi[v]);

			if (ret) {
				/* come back and try again later */
				set_bit(__I40E_MACVLAN_SYNC_PENDING,
					pf->state);
				break;
			}
		}
	}
	clear_bit(__I40E_VF_DISABLE, pf->state);
}