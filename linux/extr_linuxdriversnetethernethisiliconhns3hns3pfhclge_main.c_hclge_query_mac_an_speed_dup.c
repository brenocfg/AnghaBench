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
typedef  int /*<<< orphan*/  u8 ;
struct hclge_query_an_speed_dup_cmd {int /*<<< orphan*/  an_syn_dup_speed; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_QUERY_AN_RESULT ; 
 int /*<<< orphan*/  HCLGE_QUERY_DUPLEX_B ; 
 int /*<<< orphan*/  HCLGE_QUERY_SPEED_M ; 
 int /*<<< orphan*/  HCLGE_QUERY_SPEED_S ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int hclge_parse_speed (int,int*) ; 
 int /*<<< orphan*/  hnae3_get_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hnae3_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_query_mac_an_speed_dup(struct hclge_dev *hdev, int *speed,
					u8 *duplex)
{
	struct hclge_query_an_speed_dup_cmd *req;
	struct hclge_desc desc;
	int speed_tmp;
	int ret;

	req = (struct hclge_query_an_speed_dup_cmd *)desc.data;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_QUERY_AN_RESULT, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"mac speed/autoneg/duplex query cmd failed %d\n",
			ret);
		return ret;
	}

	*duplex = hnae3_get_bit(req->an_syn_dup_speed, HCLGE_QUERY_DUPLEX_B);
	speed_tmp = hnae3_get_field(req->an_syn_dup_speed, HCLGE_QUERY_SPEED_M,
				    HCLGE_QUERY_SPEED_S);

	ret = hclge_parse_speed(speed_tmp, speed);
	if (ret)
		dev_err(&hdev->pdev->dev,
			"could not parse speed(=%d), %d\n", speed_tmp, ret);

	return ret;
}