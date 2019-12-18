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
typedef  scalar_t__ u16 ;
struct i40e_vf {int num_tc; TYPE_1__* ch; scalar_t__ adq_enabled; } ;
struct TYPE_2__ {scalar_t__ num_qps; scalar_t__ vsi_id; } ;

/* Variables and functions */
 scalar_t__ i40e_vc_get_pf_queue_id (struct i40e_vf*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static u16 i40e_get_real_pf_qid(struct i40e_vf *vf, u16 vsi_id, u16 queue_id)
{
	int i;

	if (vf->adq_enabled) {
		/* Although VF considers all the queues(can be 1 to 16) as its
		 * own but they may actually belong to different VSIs(up to 4).
		 * We need to find which queues belongs to which VSI.
		 */
		for (i = 0; i < vf->num_tc; i++) {
			if (queue_id < vf->ch[i].num_qps) {
				vsi_id = vf->ch[i].vsi_id;
				break;
			}
			/* find right queue id which is relative to a
			 * given VSI.
			 */
			queue_id -= vf->ch[i].num_qps;
			}
		}

	return i40e_vc_get_pf_queue_id(vf, vsi_id, queue_id);
}