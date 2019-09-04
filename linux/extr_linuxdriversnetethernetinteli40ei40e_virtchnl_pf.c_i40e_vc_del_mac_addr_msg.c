#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct virtchnl_ether_addr_list {int num_elements; TYPE_1__* list; int /*<<< orphan*/  vsi_id; } ;
struct i40e_vsi {int /*<<< orphan*/  mac_filter_hash_lock; } ;
struct i40e_vf {size_t lan_vsi_idx; scalar_t__ vf_id; int /*<<< orphan*/  num_mac; int /*<<< orphan*/  vf_states; struct i40e_pf* pf; } ;
struct i40e_pf {TYPE_2__* pdev; struct i40e_vsi** vsi; } ;
typedef  scalar_t__ i40e_status ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ I40E_ERR_INVALID_MAC_ADDR ; 
 scalar_t__ I40E_ERR_PARAM ; 
 int /*<<< orphan*/  I40E_VF_STATE_ACTIVE ; 
 int /*<<< orphan*/  VIRTCHNL_OP_DEL_ETH_ADDR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ i40e_del_mac_filter (struct i40e_vsi*,scalar_t__) ; 
 scalar_t__ i40e_sync_vsi_filters (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_vc_isvalid_vsi_id (struct i40e_vf*,int /*<<< orphan*/ ) ; 
 int i40e_vc_send_resp_to_vf (struct i40e_vf*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ is_broadcast_ether_addr (scalar_t__) ; 
 scalar_t__ is_zero_ether_addr (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i40e_vc_del_mac_addr_msg(struct i40e_vf *vf, u8 *msg, u16 msglen)
{
	struct virtchnl_ether_addr_list *al =
	    (struct virtchnl_ether_addr_list *)msg;
	struct i40e_pf *pf = vf->pf;
	struct i40e_vsi *vsi = NULL;
	u16 vsi_id = al->vsi_id;
	i40e_status ret = 0;
	int i;

	if (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states) ||
	    !i40e_vc_isvalid_vsi_id(vf, vsi_id)) {
		ret = I40E_ERR_PARAM;
		goto error_param;
	}

	for (i = 0; i < al->num_elements; i++) {
		if (is_broadcast_ether_addr(al->list[i].addr) ||
		    is_zero_ether_addr(al->list[i].addr)) {
			dev_err(&pf->pdev->dev, "Invalid MAC addr %pM for VF %d\n",
				al->list[i].addr, vf->vf_id);
			ret = I40E_ERR_INVALID_MAC_ADDR;
			goto error_param;
		}
	}
	vsi = pf->vsi[vf->lan_vsi_idx];

	spin_lock_bh(&vsi->mac_filter_hash_lock);
	/* delete addresses from the list */
	for (i = 0; i < al->num_elements; i++)
		if (i40e_del_mac_filter(vsi, al->list[i].addr)) {
			ret = I40E_ERR_INVALID_MAC_ADDR;
			spin_unlock_bh(&vsi->mac_filter_hash_lock);
			goto error_param;
		} else {
			vf->num_mac--;
		}

	spin_unlock_bh(&vsi->mac_filter_hash_lock);

	/* program the updated filter list */
	ret = i40e_sync_vsi_filters(vsi);
	if (ret)
		dev_err(&pf->pdev->dev, "Unable to program VF %d MAC filters, error %d\n",
			vf->vf_id, ret);

error_param:
	/* send the response to the VF */
	return i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_DEL_ETH_ADDR,
				       ret);
}