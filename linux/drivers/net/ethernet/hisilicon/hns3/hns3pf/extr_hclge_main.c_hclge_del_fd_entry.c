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
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct TYPE_3__ {scalar_t__* rule_num; } ;
struct hclge_dev {int /*<<< orphan*/  fd_rule_lock; TYPE_2__* pdev; TYPE_1__ fd_cfg; } ;
struct ethtool_rxnfc {int /*<<< orphan*/  fs; } ;
struct ethtool_rx_flow_spec {scalar_t__ location; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 size_t HCLGE_FD_STAGE_1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  hclge_fd_rule_exist (struct hclge_dev*,scalar_t__) ; 
 int hclge_fd_tcam_config (struct hclge_dev*,size_t,int,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int hclge_fd_update_rule_list (struct hclge_dev*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hnae3_dev_fd_supported (struct hclge_dev*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclge_del_fd_entry(struct hnae3_handle *handle,
			      struct ethtool_rxnfc *cmd)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	struct ethtool_rx_flow_spec *fs;
	int ret;

	if (!hnae3_dev_fd_supported(hdev))
		return -EOPNOTSUPP;

	fs = (struct ethtool_rx_flow_spec *)&cmd->fs;

	if (fs->location >= hdev->fd_cfg.rule_num[HCLGE_FD_STAGE_1])
		return -EINVAL;

	if (!hclge_fd_rule_exist(hdev, fs->location)) {
		dev_err(&hdev->pdev->dev,
			"Delete fail, rule %d is inexistent\n", fs->location);
		return -ENOENT;
	}

	ret = hclge_fd_tcam_config(hdev, HCLGE_FD_STAGE_1, true, fs->location,
				   NULL, false);
	if (ret)
		return ret;

	spin_lock_bh(&hdev->fd_rule_lock);
	ret = hclge_fd_update_rule_list(hdev, NULL, fs->location, false);

	spin_unlock_bh(&hdev->fd_rule_lock);

	return ret;
}