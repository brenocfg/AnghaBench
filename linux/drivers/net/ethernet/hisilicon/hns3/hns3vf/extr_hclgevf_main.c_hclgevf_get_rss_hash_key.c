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
typedef  int u8 ;
typedef  int u16 ;
struct hclgevf_rss_cfg {int /*<<< orphan*/ * rss_hash_key; } ;
struct hclgevf_dev {TYPE_1__* pdev; struct hclgevf_rss_cfg rss_cfg; } ;
typedef  int /*<<< orphan*/  index ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HCLGEVF_RSS_KEY_SIZE ; 
 int HCLGEVF_RSS_MBX_RESP_LEN ; 
 int /*<<< orphan*/  HCLGE_MBX_GET_RSS_KEY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclgevf_send_mbx_msg (struct hclgevf_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int,int*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static int hclgevf_get_rss_hash_key(struct hclgevf_dev *hdev)
{
#define HCLGEVF_RSS_MBX_RESP_LEN	8

	struct hclgevf_rss_cfg *rss_cfg = &hdev->rss_cfg;
	u8 resp_msg[HCLGEVF_RSS_MBX_RESP_LEN];
	u16 msg_num, hash_key_index;
	u8 index;
	int ret;

	msg_num = (HCLGEVF_RSS_KEY_SIZE + HCLGEVF_RSS_MBX_RESP_LEN - 1) /
			HCLGEVF_RSS_MBX_RESP_LEN;
	for (index = 0; index < msg_num; index++) {
		ret = hclgevf_send_mbx_msg(hdev, HCLGE_MBX_GET_RSS_KEY, 0,
					   &index, sizeof(index),
					   true, resp_msg,
					   HCLGEVF_RSS_MBX_RESP_LEN);
		if (ret) {
			dev_err(&hdev->pdev->dev,
				"VF get rss hash key from PF failed, ret=%d",
				ret);
			return ret;
		}

		hash_key_index = HCLGEVF_RSS_MBX_RESP_LEN * index;
		if (index == msg_num - 1)
			memcpy(&rss_cfg->rss_hash_key[hash_key_index],
			       &resp_msg[0],
			       HCLGEVF_RSS_KEY_SIZE - hash_key_index);
		else
			memcpy(&rss_cfg->rss_hash_key[hash_key_index],
			       &resp_msg[0], HCLGEVF_RSS_MBX_RESP_LEN);
	}

	return 0;
}