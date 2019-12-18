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
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_fd_rule_tuples {int dummy; } ;
struct hclge_fd_rule {int location; scalar_t__ queue_id; scalar_t__ flow_id; } ;
struct TYPE_2__ {scalar_t__* rule_num; } ;
struct hclge_dev {scalar_t__ fd_active_type; int /*<<< orphan*/  fd_rule_lock; int /*<<< orphan*/  fd_bmap; TYPE_1__ fd_cfg; } ;
struct flow_keys {int dummy; } ;
typedef  int /*<<< orphan*/  new_tuples ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ HCLGE_FD_EP_ACTIVE ; 
 size_t HCLGE_FD_STAGE_1 ; 
 int /*<<< orphan*/  MAX_FD_FILTER_NUM ; 
 scalar_t__ find_first_zero_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hclge_config_action (struct hclge_dev*,size_t,struct hclge_fd_rule*) ; 
 int /*<<< orphan*/  hclge_fd_build_arfs_rule (struct hclge_fd_rule_tuples*,struct hclge_fd_rule*) ; 
 int hclge_fd_config_rule (struct hclge_dev*,struct hclge_fd_rule*) ; 
 int /*<<< orphan*/  hclge_fd_get_flow_tuples (struct flow_keys*,struct hclge_fd_rule_tuples*) ; 
 struct hclge_fd_rule* hclge_fd_search_flow_keys (struct hclge_dev*,struct hclge_fd_rule_tuples*) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hnae3_dev_fd_supported (struct hclge_dev*) ; 
 struct hclge_fd_rule* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct hclge_fd_rule_tuples*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclge_add_fd_entry_by_arfs(struct hnae3_handle *handle, u16 queue_id,
				      u16 flow_id, struct flow_keys *fkeys)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_fd_rule_tuples new_tuples;
	struct hclge_dev *hdev = vport->back;
	struct hclge_fd_rule *rule;
	u16 tmp_queue_id;
	u16 bit_id;
	int ret;

	if (!hnae3_dev_fd_supported(hdev))
		return -EOPNOTSUPP;

	memset(&new_tuples, 0, sizeof(new_tuples));
	hclge_fd_get_flow_tuples(fkeys, &new_tuples);

	spin_lock_bh(&hdev->fd_rule_lock);

	/* when there is already fd rule existed add by user,
	 * arfs should not work
	 */
	if (hdev->fd_active_type == HCLGE_FD_EP_ACTIVE) {
		spin_unlock_bh(&hdev->fd_rule_lock);

		return -EOPNOTSUPP;
	}

	/* check is there flow director filter existed for this flow,
	 * if not, create a new filter for it;
	 * if filter exist with different queue id, modify the filter;
	 * if filter exist with same queue id, do nothing
	 */
	rule = hclge_fd_search_flow_keys(hdev, &new_tuples);
	if (!rule) {
		bit_id = find_first_zero_bit(hdev->fd_bmap, MAX_FD_FILTER_NUM);
		if (bit_id >= hdev->fd_cfg.rule_num[HCLGE_FD_STAGE_1]) {
			spin_unlock_bh(&hdev->fd_rule_lock);

			return -ENOSPC;
		}

		rule = kzalloc(sizeof(*rule), GFP_ATOMIC);
		if (!rule) {
			spin_unlock_bh(&hdev->fd_rule_lock);

			return -ENOMEM;
		}

		set_bit(bit_id, hdev->fd_bmap);
		rule->location = bit_id;
		rule->flow_id = flow_id;
		rule->queue_id = queue_id;
		hclge_fd_build_arfs_rule(&new_tuples, rule);
		ret = hclge_fd_config_rule(hdev, rule);

		spin_unlock_bh(&hdev->fd_rule_lock);

		if (ret)
			return ret;

		return rule->location;
	}

	spin_unlock_bh(&hdev->fd_rule_lock);

	if (rule->queue_id == queue_id)
		return rule->location;

	tmp_queue_id = rule->queue_id;
	rule->queue_id = queue_id;
	ret = hclge_config_action(hdev, HCLGE_FD_STAGE_1, rule);
	if (ret) {
		rule->queue_id = tmp_queue_id;
		return ret;
	}

	return rule->location;
}