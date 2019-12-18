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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct virtchnl_vf_res_request {scalar_t__ num_queue_pairs; } ;
struct i40e_vf {scalar_t__ num_queue_pairs; scalar_t__ num_req_queues; int /*<<< orphan*/  vf_id; int /*<<< orphan*/  vf_states; struct i40e_pf* pf; } ;
struct i40e_pf {scalar_t__ queues_left; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ I40E_MAX_VF_QUEUES ; 
 int /*<<< orphan*/  I40E_VF_STATE_ACTIVE ; 
 int /*<<< orphan*/  VIRTCHNL_OP_REQUEST_QUEUES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  i40e_reset_vf (struct i40e_vf*,int) ; 
 int /*<<< orphan*/  i40e_vc_notify_vf_reset (struct i40e_vf*) ; 
 int i40e_vc_send_msg_to_vf (struct i40e_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i40e_vc_request_queues_msg(struct i40e_vf *vf, u8 *msg)
{
	struct virtchnl_vf_res_request *vfres =
		(struct virtchnl_vf_res_request *)msg;
	u16 req_pairs = vfres->num_queue_pairs;
	u8 cur_pairs = vf->num_queue_pairs;
	struct i40e_pf *pf = vf->pf;

	if (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states))
		return -EINVAL;

	if (req_pairs > I40E_MAX_VF_QUEUES) {
		dev_err(&pf->pdev->dev,
			"VF %d tried to request more than %d queues.\n",
			vf->vf_id,
			I40E_MAX_VF_QUEUES);
		vfres->num_queue_pairs = I40E_MAX_VF_QUEUES;
	} else if (req_pairs - cur_pairs > pf->queues_left) {
		dev_warn(&pf->pdev->dev,
			 "VF %d requested %d more queues, but only %d left.\n",
			 vf->vf_id,
			 req_pairs - cur_pairs,
			 pf->queues_left);
		vfres->num_queue_pairs = pf->queues_left + cur_pairs;
	} else {
		/* successful request */
		vf->num_req_queues = req_pairs;
		i40e_vc_notify_vf_reset(vf);
		i40e_reset_vf(vf, false);
		return 0;
	}

	return i40e_vc_send_msg_to_vf(vf, VIRTCHNL_OP_REQUEST_QUEUES, 0,
				      (u8 *)vfres, sizeof(*vfres));
}