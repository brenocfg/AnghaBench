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
typedef  int /*<<< orphan*/  u8 ;
struct hnae3_knic_private_info {int num_tqps; } ;
struct hnae3_handle {int dummy; } ;
struct TYPE_4__ {struct hnae3_knic_private_info kinfo; } ;
struct hclge_vport {TYPE_2__ nic; struct hclge_dev* back; } ;
struct hclge_dev {TYPE_1__* pdev; } ;
typedef  enum hnae3_loop { ____Placeholder_hnae3_loop } hnae3_loop ;
struct TYPE_3__ {int revision; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  HCLGE_SWITCH_ALW_LPBK_B ; 
 int /*<<< orphan*/  HCLGE_SWITCH_ALW_LPBK_MASK ; 
#define  HNAE3_LOOP_APP 131 
#define  HNAE3_LOOP_PARALLEL_SERDES 130 
#define  HNAE3_LOOP_PHY 129 
#define  HNAE3_LOOP_SERIAL_SERDES 128 
 int /*<<< orphan*/  PF_VPORT_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_config_switch_param (struct hclge_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int hclge_set_app_loopback (struct hclge_dev*,int) ; 
 int hclge_set_phy_loopback (struct hclge_dev*,int) ; 
 int hclge_set_serdes_loopback (struct hclge_dev*,int,int) ; 
 int hclge_tqp_enable (struct hclge_dev*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_set_loopback(struct hnae3_handle *handle,
			      enum hnae3_loop loop_mode, bool en)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hnae3_knic_private_info *kinfo;
	struct hclge_dev *hdev = vport->back;
	int i, ret;

	/* Loopback can be enabled in three places: SSU, MAC, and serdes. By
	 * default, SSU loopback is enabled, so if the SMAC and the DMAC are
	 * the same, the packets are looped back in the SSU. If SSU loopback
	 * is disabled, packets can reach MAC even if SMAC is the same as DMAC.
	 */
	if (hdev->pdev->revision >= 0x21) {
		u8 switch_param = en ? 0 : BIT(HCLGE_SWITCH_ALW_LPBK_B);

		ret = hclge_config_switch_param(hdev, PF_VPORT_ID, switch_param,
						HCLGE_SWITCH_ALW_LPBK_MASK);
		if (ret)
			return ret;
	}

	switch (loop_mode) {
	case HNAE3_LOOP_APP:
		ret = hclge_set_app_loopback(hdev, en);
		break;
	case HNAE3_LOOP_SERIAL_SERDES:
	case HNAE3_LOOP_PARALLEL_SERDES:
		ret = hclge_set_serdes_loopback(hdev, en, loop_mode);
		break;
	case HNAE3_LOOP_PHY:
		ret = hclge_set_phy_loopback(hdev, en);
		break;
	default:
		ret = -ENOTSUPP;
		dev_err(&hdev->pdev->dev,
			"loop_mode %d is not supported\n", loop_mode);
		break;
	}

	if (ret)
		return ret;

	kinfo = &vport->nic.kinfo;
	for (i = 0; i < kinfo->num_tqps; i++) {
		ret = hclge_tqp_enable(hdev, i, 0, en);
		if (ret)
			return ret;
	}

	return 0;
}