#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_13__ {int link_status; int link_speed; } ;
struct TYPE_14__ {TYPE_6__ link_event; } ;
struct virtchnl_pf_event {TYPE_7__ event_data; int /*<<< orphan*/  severity; int /*<<< orphan*/  event; } ;
struct net_device {int dummy; } ;
struct i40e_vf {int vf_id; int link_forced; int link_up; } ;
struct TYPE_11__ {int link_info; int /*<<< orphan*/  link_speed; } ;
struct TYPE_12__ {TYPE_4__ link_info; } ;
struct TYPE_10__ {int vf_base_id; } ;
struct i40e_hw {TYPE_5__ phy; TYPE_3__ func_caps; } ;
struct i40e_pf {int num_alloc_vfs; int /*<<< orphan*/  state; struct i40e_hw hw; struct i40e_vf* vf; TYPE_2__* pdev; } ;
struct i40e_netdev_priv {TYPE_1__* vsi; } ;
typedef  int /*<<< orphan*/  pfe ;
typedef  enum virtchnl_link_speed { ____Placeholder_virtchnl_link_speed } virtchnl_link_speed ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {struct i40e_pf* back; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int I40E_AQ_LINK_UP ; 
#define  IFLA_VF_LINK_STATE_AUTO 130 
#define  IFLA_VF_LINK_STATE_DISABLE 129 
#define  IFLA_VF_LINK_STATE_ENABLE 128 
 int /*<<< orphan*/  PF_EVENT_SEVERITY_INFO ; 
 int /*<<< orphan*/  VIRTCHNL_EVENT_LINK_CHANGE ; 
 int VIRTCHNL_LINK_SPEED_40GB ; 
 int /*<<< orphan*/  VIRTCHNL_OP_EVENT ; 
 int /*<<< orphan*/  __I40E_VIRTCHNL_OP_PENDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i40e_aq_send_msg_to_vf (struct i40e_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int i40e_ndo_set_vf_link_state(struct net_device *netdev, int vf_id, int link)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_pf *pf = np->vsi->back;
	struct virtchnl_pf_event pfe;
	struct i40e_hw *hw = &pf->hw;
	struct i40e_vf *vf;
	int abs_vf_id;
	int ret = 0;

	if (test_and_set_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state)) {
		dev_warn(&pf->pdev->dev, "Unable to configure VFs, other operation is pending.\n");
		return -EAGAIN;
	}

	/* validate the request */
	if (vf_id >= pf->num_alloc_vfs) {
		dev_err(&pf->pdev->dev, "Invalid VF Identifier %d\n", vf_id);
		ret = -EINVAL;
		goto error_out;
	}

	vf = &pf->vf[vf_id];
	abs_vf_id = vf->vf_id + hw->func_caps.vf_base_id;

	pfe.event = VIRTCHNL_EVENT_LINK_CHANGE;
	pfe.severity = PF_EVENT_SEVERITY_INFO;

	switch (link) {
	case IFLA_VF_LINK_STATE_AUTO:
		vf->link_forced = false;
		pfe.event_data.link_event.link_status =
			pf->hw.phy.link_info.link_info & I40E_AQ_LINK_UP;
		pfe.event_data.link_event.link_speed =
			(enum virtchnl_link_speed)
			pf->hw.phy.link_info.link_speed;
		break;
	case IFLA_VF_LINK_STATE_ENABLE:
		vf->link_forced = true;
		vf->link_up = true;
		pfe.event_data.link_event.link_status = true;
		pfe.event_data.link_event.link_speed = VIRTCHNL_LINK_SPEED_40GB;
		break;
	case IFLA_VF_LINK_STATE_DISABLE:
		vf->link_forced = true;
		vf->link_up = false;
		pfe.event_data.link_event.link_status = false;
		pfe.event_data.link_event.link_speed = 0;
		break;
	default:
		ret = -EINVAL;
		goto error_out;
	}
	/* Notify the VF of its new link state */
	i40e_aq_send_msg_to_vf(hw, abs_vf_id, VIRTCHNL_OP_EVENT,
			       0, (u8 *)&pfe, sizeof(pfe), NULL);

error_out:
	clear_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state);
	return ret;
}