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
typedef  scalar_t__ u16 ;
struct hclge_dev {int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct hclge_cfg_tso_status_cmd {void* tso_mss_max; void* tso_mss_min; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_TSO_GENERIC_CONFIG ; 
 int /*<<< orphan*/  HCLGE_TSO_MSS_MIN_M ; 
 int /*<<< orphan*/  HCLGE_TSO_MSS_MIN_S ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_field (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int hclge_config_tso(struct hclge_dev *hdev, unsigned int tso_mss_min,
			    unsigned int tso_mss_max)
{
	struct hclge_cfg_tso_status_cmd *req;
	struct hclge_desc desc;
	u16 tso_mss;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TSO_GENERIC_CONFIG, false);

	req = (struct hclge_cfg_tso_status_cmd *)desc.data;

	tso_mss = 0;
	hnae3_set_field(tso_mss, HCLGE_TSO_MSS_MIN_M,
			HCLGE_TSO_MSS_MIN_S, tso_mss_min);
	req->tso_mss_min = cpu_to_le16(tso_mss);

	tso_mss = 0;
	hnae3_set_field(tso_mss, HCLGE_TSO_MSS_MIN_M,
			HCLGE_TSO_MSS_MIN_S, tso_mss_max);
	req->tso_mss_max = cpu_to_le16(tso_mss);

	return hclge_cmd_send(&hdev->hw, &desc, 1);
}