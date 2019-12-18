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
struct i40e_vf {int num_tc; TYPE_1__* ch; struct i40e_pf* pf; } ;
struct i40e_pf {int /*<<< orphan*/ * vsi; } ;
struct TYPE_2__ {int vsi_idx; scalar_t__ vsi_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_vsi_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_del_qch(struct i40e_vf *vf)
{
	struct i40e_pf *pf = vf->pf;
	int i;

	/* first element in the array belongs to primary VF VSI and we shouldn't
	 * delete it. We should however delete the rest of the VSIs created
	 */
	for (i = 1; i < vf->num_tc; i++) {
		if (vf->ch[i].vsi_idx) {
			i40e_vsi_release(pf->vsi[vf->ch[i].vsi_idx]);
			vf->ch[i].vsi_idx = 0;
			vf->ch[i].vsi_id = 0;
		}
	}
}