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
struct hclge_mac_ethertype_idx_rd_cmd {int index; int* mac_addr; int flags; int ethter_type; int vlan_tag; int i_port_bitmap; int i_port_direction; int egress_port; int egress_queue; int /*<<< orphan*/  resp_code; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HCLGE_DBG_BUF_LEN ; 
 int HCLGE_DBG_MNG_DROP_B ; 
 int HCLGE_DBG_MNG_ETHER_MASK_B ; 
 int HCLGE_DBG_MNG_E_TYPE_B ; 
 int HCLGE_DBG_MNG_MAC_MASK_B ; 
 int HCLGE_DBG_MNG_PF_ID ; 
 int HCLGE_DBG_MNG_TBL_MAX ; 
 int HCLGE_DBG_MNG_VF_ID ; 
 int HCLGE_DBG_MNG_VLAN_MASK_B ; 
 int HCLGE_DBG_MNG_VLAN_TAG ; 
 int /*<<< orphan*/  HCLGE_MAC_ETHERTYPE_IDX_RD ; 
 int cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int,int,...) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 

__attribute__((used)) static void hclge_dbg_dump_mng_table(struct hclge_dev *hdev)
{
	struct hclge_mac_ethertype_idx_rd_cmd *req0;
	char printf_buf[HCLGE_DBG_BUF_LEN];
	struct hclge_desc desc;
	int ret, i;

	dev_info(&hdev->pdev->dev, "mng tab:\n");
	memset(printf_buf, 0, HCLGE_DBG_BUF_LEN);
	strncat(printf_buf,
		"entry|mac_addr         |mask|ether|mask|vlan|mask",
		HCLGE_DBG_BUF_LEN - 1);
	strncat(printf_buf + strlen(printf_buf),
		"|i_map|i_dir|e_type|pf_id|vf_id|q_id|drop\n",
		HCLGE_DBG_BUF_LEN - strlen(printf_buf) - 1);

	dev_info(&hdev->pdev->dev, "%s", printf_buf);

	for (i = 0; i < HCLGE_DBG_MNG_TBL_MAX; i++) {
		hclge_cmd_setup_basic_desc(&desc, HCLGE_MAC_ETHERTYPE_IDX_RD,
					   true);
		req0 = (struct hclge_mac_ethertype_idx_rd_cmd *)&desc.data;
		req0->index = cpu_to_le16(i);

		ret = hclge_cmd_send(&hdev->hw, &desc, 1);
		if (ret) {
			dev_err(&hdev->pdev->dev,
				"call hclge_cmd_send fail, ret = %d\n", ret);
			return;
		}

		if (!req0->resp_code)
			continue;

		memset(printf_buf, 0, HCLGE_DBG_BUF_LEN);
		snprintf(printf_buf, HCLGE_DBG_BUF_LEN,
			 "%02u   |%02x:%02x:%02x:%02x:%02x:%02x|",
			 req0->index, req0->mac_addr[0], req0->mac_addr[1],
			 req0->mac_addr[2], req0->mac_addr[3],
			 req0->mac_addr[4], req0->mac_addr[5]);

		snprintf(printf_buf + strlen(printf_buf),
			 HCLGE_DBG_BUF_LEN - strlen(printf_buf),
			 "%x   |%04x |%x   |%04x|%x   |%02x   |%02x   |",
			 !!(req0->flags & HCLGE_DBG_MNG_MAC_MASK_B),
			 req0->ethter_type,
			 !!(req0->flags & HCLGE_DBG_MNG_ETHER_MASK_B),
			 req0->vlan_tag & HCLGE_DBG_MNG_VLAN_TAG,
			 !!(req0->flags & HCLGE_DBG_MNG_VLAN_MASK_B),
			 req0->i_port_bitmap, req0->i_port_direction);

		snprintf(printf_buf + strlen(printf_buf),
			 HCLGE_DBG_BUF_LEN - strlen(printf_buf),
			 "%d     |%d    |%02d   |%04d|%x\n",
			 !!(req0->egress_port & HCLGE_DBG_MNG_E_TYPE_B),
			 req0->egress_port & HCLGE_DBG_MNG_PF_ID,
			 (req0->egress_port >> 3) & HCLGE_DBG_MNG_VF_ID,
			 req0->egress_queue,
			 !!(req0->egress_port & HCLGE_DBG_MNG_DROP_B));

		dev_info(&hdev->pdev->dev, "%s", printf_buf);
	}
}