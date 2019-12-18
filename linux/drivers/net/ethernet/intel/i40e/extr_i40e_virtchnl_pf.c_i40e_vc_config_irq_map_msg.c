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
typedef  int /*<<< orphan*/  u16 ;
struct virtchnl_vector_map {int /*<<< orphan*/  txq_map; int /*<<< orphan*/  rxq_map; int /*<<< orphan*/  vsi_id; int /*<<< orphan*/  vector_id; } ;
struct virtchnl_irq_map_info {int num_vectors; struct virtchnl_vector_map* vecmap; } ;
struct i40e_vf {TYPE_3__* pf; int /*<<< orphan*/  vf_states; } ;
typedef  int /*<<< orphan*/  i40e_status ;
struct TYPE_4__ {int num_msix_vectors_vf; } ;
struct TYPE_5__ {TYPE_1__ func_caps; } ;
struct TYPE_6__ {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ERR_PARAM ; 
 int /*<<< orphan*/  I40E_VF_STATE_ACTIVE ; 
 int /*<<< orphan*/  VIRTCHNL_OP_CONFIG_IRQ_MAP ; 
 int /*<<< orphan*/  i40e_config_irq_link_list (struct i40e_vf*,int /*<<< orphan*/ ,struct virtchnl_vector_map*) ; 
 scalar_t__ i40e_validate_queue_map (struct i40e_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_vc_isvalid_vector_id (struct i40e_vf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_vc_isvalid_vsi_id (struct i40e_vf*,int /*<<< orphan*/ ) ; 
 int i40e_vc_send_resp_to_vf (struct i40e_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i40e_vc_config_irq_map_msg(struct i40e_vf *vf, u8 *msg)
{
	struct virtchnl_irq_map_info *irqmap_info =
	    (struct virtchnl_irq_map_info *)msg;
	struct virtchnl_vector_map *map;
	u16 vsi_id;
	i40e_status aq_ret = 0;
	int i;

	if (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states)) {
		aq_ret = I40E_ERR_PARAM;
		goto error_param;
	}

	if (irqmap_info->num_vectors >
	    vf->pf->hw.func_caps.num_msix_vectors_vf) {
		aq_ret = I40E_ERR_PARAM;
		goto error_param;
	}

	for (i = 0; i < irqmap_info->num_vectors; i++) {
		map = &irqmap_info->vecmap[i];
		/* validate msg params */
		if (!i40e_vc_isvalid_vector_id(vf, map->vector_id) ||
		    !i40e_vc_isvalid_vsi_id(vf, map->vsi_id)) {
			aq_ret = I40E_ERR_PARAM;
			goto error_param;
		}
		vsi_id = map->vsi_id;

		if (i40e_validate_queue_map(vf, vsi_id, map->rxq_map)) {
			aq_ret = I40E_ERR_PARAM;
			goto error_param;
		}

		if (i40e_validate_queue_map(vf, vsi_id, map->txq_map)) {
			aq_ret = I40E_ERR_PARAM;
			goto error_param;
		}

		i40e_config_irq_link_list(vf, vsi_id, map);
	}
error_param:
	/* send the response to the VF */
	return i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_CONFIG_IRQ_MAP,
				       aq_ret);
}