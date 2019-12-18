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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct hnae3_handle {int dummy; } ;
struct hclge_vport {scalar_t__ vport_id; scalar_t__ alloc_tqps; struct hclge_dev* back; } ;
struct hclge_fd_rule {int action; int /*<<< orphan*/  rule_type; scalar_t__ queue_id; scalar_t__ vf_id; scalar_t__ unused_tuple; int /*<<< orphan*/  location; int /*<<< orphan*/  flow_type; } ;
struct hclge_dev {int num_req_vfs; int /*<<< orphan*/  fd_rule_lock; TYPE_2__* pdev; TYPE_1__* vport; int /*<<< orphan*/  fd_en; } ;
struct ethtool_rxnfc {int /*<<< orphan*/  fs; } ;
struct ethtool_rx_flow_spec {scalar_t__ ring_cookie; int /*<<< orphan*/  location; int /*<<< orphan*/  flow_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ vport_id; scalar_t__ alloc_tqps; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HCLGE_FD_ACTION_ACCEPT_PACKET ; 
 int HCLGE_FD_ACTION_DROP_PACKET ; 
 int /*<<< orphan*/  HCLGE_FD_EP_ACTIVE ; 
 scalar_t__ RX_CLS_FLOW_DISC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ethtool_get_flow_spec_ring (scalar_t__) ; 
 int ethtool_get_flow_spec_ring_vf (scalar_t__) ; 
 int /*<<< orphan*/  hclge_clear_arfs_rules (struct hnae3_handle*) ; 
 int hclge_fd_check_spec (struct hclge_dev*,struct ethtool_rx_flow_spec*,scalar_t__*) ; 
 int hclge_fd_config_rule (struct hclge_dev*,struct hclge_fd_rule*) ; 
 int hclge_fd_get_tuple (struct hclge_dev*,struct ethtool_rx_flow_spec*,struct hclge_fd_rule*) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hnae3_dev_fd_supported (struct hclge_dev*) ; 
 int /*<<< orphan*/  kfree (struct hclge_fd_rule*) ; 
 struct hclge_fd_rule* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclge_add_fd_entry(struct hnae3_handle *handle,
			      struct ethtool_rxnfc *cmd)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	u16 dst_vport_id = 0, q_index = 0;
	struct ethtool_rx_flow_spec *fs;
	struct hclge_fd_rule *rule;
	u32 unused = 0;
	u8 action;
	int ret;

	if (!hnae3_dev_fd_supported(hdev))
		return -EOPNOTSUPP;

	if (!hdev->fd_en) {
		dev_warn(&hdev->pdev->dev,
			 "Please enable flow director first\n");
		return -EOPNOTSUPP;
	}

	fs = (struct ethtool_rx_flow_spec *)&cmd->fs;

	ret = hclge_fd_check_spec(hdev, fs, &unused);
	if (ret) {
		dev_err(&hdev->pdev->dev, "Check fd spec failed\n");
		return ret;
	}

	if (fs->ring_cookie == RX_CLS_FLOW_DISC) {
		action = HCLGE_FD_ACTION_DROP_PACKET;
	} else {
		u32 ring = ethtool_get_flow_spec_ring(fs->ring_cookie);
		u8 vf = ethtool_get_flow_spec_ring_vf(fs->ring_cookie);
		u16 tqps;

		if (vf > hdev->num_req_vfs) {
			dev_err(&hdev->pdev->dev,
				"Error: vf id (%d) > max vf num (%d)\n",
				vf, hdev->num_req_vfs);
			return -EINVAL;
		}

		dst_vport_id = vf ? hdev->vport[vf].vport_id : vport->vport_id;
		tqps = vf ? hdev->vport[vf].alloc_tqps : vport->alloc_tqps;

		if (ring >= tqps) {
			dev_err(&hdev->pdev->dev,
				"Error: queue id (%d) > max tqp num (%d)\n",
				ring, tqps - 1);
			return -EINVAL;
		}

		action = HCLGE_FD_ACTION_ACCEPT_PACKET;
		q_index = ring;
	}

	rule = kzalloc(sizeof(*rule), GFP_KERNEL);
	if (!rule)
		return -ENOMEM;

	ret = hclge_fd_get_tuple(hdev, fs, rule);
	if (ret) {
		kfree(rule);
		return ret;
	}

	rule->flow_type = fs->flow_type;

	rule->location = fs->location;
	rule->unused_tuple = unused;
	rule->vf_id = dst_vport_id;
	rule->queue_id = q_index;
	rule->action = action;
	rule->rule_type = HCLGE_FD_EP_ACTIVE;

	/* to avoid rule conflict, when user configure rule by ethtool,
	 * we need to clear all arfs rules
	 */
	hclge_clear_arfs_rules(handle);

	spin_lock_bh(&hdev->fd_rule_lock);
	ret = hclge_fd_config_rule(hdev, rule);

	spin_unlock_bh(&hdev->fd_rule_lock);

	return ret;
}