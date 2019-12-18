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
struct hclge_fd_rule {int /*<<< orphan*/  location; } ;
struct hclge_dev {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HCLGE_FD_STAGE_1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int hclge_config_action (struct hclge_dev*,int /*<<< orphan*/ ,struct hclge_fd_rule*) ; 
 int hclge_config_key (struct hclge_dev*,int /*<<< orphan*/ ,struct hclge_fd_rule*) ; 
 int /*<<< orphan*/  hclge_fd_update_rule_list (struct hclge_dev*,struct hclge_fd_rule*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_fd_config_rule(struct hclge_dev *hdev,
				struct hclge_fd_rule *rule)
{
	int ret;

	if (!rule) {
		dev_err(&hdev->pdev->dev,
			"The flow director rule is NULL\n");
		return -EINVAL;
	}

	/* it will never fail here, so needn't to check return value */
	hclge_fd_update_rule_list(hdev, rule, rule->location, true);

	ret = hclge_config_action(hdev, HCLGE_FD_STAGE_1, rule);
	if (ret)
		goto clear_rule;

	ret = hclge_config_key(hdev, HCLGE_FD_STAGE_1, rule);
	if (ret)
		goto clear_rule;

	return 0;

clear_rule:
	hclge_fd_update_rule_list(hdev, rule, rule->location, false);
	return ret;
}