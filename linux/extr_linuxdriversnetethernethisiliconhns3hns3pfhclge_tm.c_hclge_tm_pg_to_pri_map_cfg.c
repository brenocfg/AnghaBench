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
struct hclge_pg_to_pri_link_cmd {void* pri_bit_map; void* pg_id; } ;
struct hclge_dev {int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_TM_PG_TO_PRI_LINK ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_tm_pg_to_pri_map_cfg(struct hclge_dev *hdev,
				      u8 pg_id, u8 pri_bit_map)
{
	struct hclge_pg_to_pri_link_cmd *map;
	struct hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_PG_TO_PRI_LINK, false);

	map = (struct hclge_pg_to_pri_link_cmd *)desc.data;

	map->pg_id = pg_id;
	map->pri_bit_map = pri_bit_map;

	return hclge_cmd_send(&hdev->hw, &desc, 1);
}