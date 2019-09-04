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
typedef  void* u8 ;
struct hclge_pg_weight_cmd {void* dwrr; void* pg_id; } ;
struct hclge_dev {int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_TM_PG_WEIGHT ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_tm_pg_weight_cfg(struct hclge_dev *hdev, u8 pg_id,
				  u8 dwrr)
{
	struct hclge_pg_weight_cmd *weight;
	struct hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_PG_WEIGHT, false);

	weight = (struct hclge_pg_weight_cmd *)desc.data;

	weight->pg_id = pg_id;
	weight->dwrr = dwrr;

	return hclge_cmd_send(&hdev->hw, &desc, 1);
}