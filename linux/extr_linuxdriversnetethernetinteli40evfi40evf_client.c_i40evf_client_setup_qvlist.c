#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct virtchnl_iwarp_qvlist_info {int num_vectors; } ;
struct virtchnl_iwarp_qv_info {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  asq_last_status; } ;
struct TYPE_6__ {TYPE_2__ aq; } ;
struct i40evf_adapter {size_t iwarp_base_vector; size_t num_iwarp_msix; int client_pending; TYPE_3__ hw; TYPE_1__* pdev; scalar_t__ aq_required; } ;
struct i40e_qvlist_info {size_t num_vectors; struct i40e_qv_info* qv_info; } ;
struct i40e_qv_info {size_t v_idx; } ;
struct i40e_info {struct i40evf_adapter* vf; } ;
struct i40e_client {int dummy; } ;
typedef  int i40e_status ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  I40E_SUCCESS ; 
 int /*<<< orphan*/  VIRTCHNL_OP_CONFIG_IWARP_IRQ_MAP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int i40e_aq_send_msg_to_pf (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int i40evf_client_setup_qvlist(struct i40e_info *ldev,
				      struct i40e_client *client,
				      struct i40e_qvlist_info *qvlist_info)
{
	struct virtchnl_iwarp_qvlist_info *v_qvlist_info;
	struct i40evf_adapter *adapter = ldev->vf;
	struct i40e_qv_info *qv_info;
	i40e_status err;
	u32 v_idx, i;
	u32 msg_size;

	if (adapter->aq_required)
		return -EAGAIN;

	/* A quick check on whether the vectors belong to the client */
	for (i = 0; i < qvlist_info->num_vectors; i++) {
		qv_info = &qvlist_info->qv_info[i];
		if (!qv_info)
			continue;
		v_idx = qv_info->v_idx;
		if ((v_idx >=
		    (adapter->iwarp_base_vector + adapter->num_iwarp_msix)) ||
		    (v_idx < adapter->iwarp_base_vector))
			return -EINVAL;
	}

	v_qvlist_info = (struct virtchnl_iwarp_qvlist_info *)qvlist_info;
	msg_size = sizeof(struct virtchnl_iwarp_qvlist_info) +
			(sizeof(struct virtchnl_iwarp_qv_info) *
			(v_qvlist_info->num_vectors - 1));

	adapter->client_pending |= BIT(VIRTCHNL_OP_CONFIG_IWARP_IRQ_MAP);
	err = i40e_aq_send_msg_to_pf(&adapter->hw,
			VIRTCHNL_OP_CONFIG_IWARP_IRQ_MAP,
			I40E_SUCCESS, (u8 *)v_qvlist_info, msg_size, NULL);

	if (err) {
		dev_err(&adapter->pdev->dev,
			"Unable to send iWarp vector config message to PF, error %d, aq status %d\n",
			err, adapter->hw.aq.asq_last_status);
		goto out;
	}

	err = -EBUSY;
	for (i = 0; i < 5; i++) {
		msleep(100);
		if (!(adapter->client_pending &
		      BIT(VIRTCHNL_OP_CONFIG_IWARP_IRQ_MAP))) {
			err = 0;
			break;
		}
	}
out:
	return err;
}