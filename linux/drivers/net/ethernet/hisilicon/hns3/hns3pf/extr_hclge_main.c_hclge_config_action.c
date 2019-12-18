#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct hclge_fd_rule {scalar_t__ action; int /*<<< orphan*/  location; scalar_t__ queue_id; } ;
struct hclge_fd_ad_data {int drop_packet; int forward_to_direct_queue; int use_counter; int use_next_stage; int write_rule_id_to_bd; int /*<<< orphan*/  ad_id; int /*<<< orphan*/  rule_id; scalar_t__ next_input_key; scalar_t__ counter_id; scalar_t__ queue_id; } ;
struct hclge_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ HCLGE_FD_ACTION_DROP_PACKET ; 
 int hclge_fd_ad_config (struct hclge_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hclge_fd_ad_data*) ; 

__attribute__((used)) static int hclge_config_action(struct hclge_dev *hdev, u8 stage,
			       struct hclge_fd_rule *rule)
{
	struct hclge_fd_ad_data ad_data;

	ad_data.ad_id = rule->location;

	if (rule->action == HCLGE_FD_ACTION_DROP_PACKET) {
		ad_data.drop_packet = true;
		ad_data.forward_to_direct_queue = false;
		ad_data.queue_id = 0;
	} else {
		ad_data.drop_packet = false;
		ad_data.forward_to_direct_queue = true;
		ad_data.queue_id = rule->queue_id;
	}

	ad_data.use_counter = false;
	ad_data.counter_id = 0;

	ad_data.use_next_stage = false;
	ad_data.next_input_key = 0;

	ad_data.write_rule_id_to_bd = true;
	ad_data.rule_id = rule->location;

	return hclge_fd_ad_config(hdev, stage, ad_data.ad_id, &ad_data);
}