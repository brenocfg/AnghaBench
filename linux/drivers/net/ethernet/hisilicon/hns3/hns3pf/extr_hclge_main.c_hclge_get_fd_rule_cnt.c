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
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct TYPE_2__ {int /*<<< orphan*/ * rule_num; } ;
struct hclge_dev {TYPE_1__ fd_cfg; int /*<<< orphan*/  hclge_fd_rule_num; } ;
struct ethtool_rxnfc {int /*<<< orphan*/  data; int /*<<< orphan*/  rule_cnt; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 size_t HCLGE_FD_STAGE_1 ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hnae3_dev_fd_supported (struct hclge_dev*) ; 

__attribute__((used)) static int hclge_get_fd_rule_cnt(struct hnae3_handle *handle,
				 struct ethtool_rxnfc *cmd)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;

	if (!hnae3_dev_fd_supported(hdev))
		return -EOPNOTSUPP;

	cmd->rule_cnt = hdev->hclge_fd_rule_num;
	cmd->data = hdev->fd_cfg.rule_num[HCLGE_FD_STAGE_1];

	return 0;
}