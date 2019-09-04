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
struct hnae3_handle {int dummy; } ;
struct hclgevf_rss_config_cmd {int hash_config; int /*<<< orphan*/  hash_key; } ;
struct hclgevf_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclgevf_desc {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_RSS_HASH_TOP ; 
 int /*<<< orphan*/  ETH_RSS_HASH_UNKNOWN ; 
 int /*<<< orphan*/  HCLGEVF_OPC_RSS_GENERIC_CONFIG ; 
 int HCLGEVF_RSS_HASH_ALGO_TOEPLITZ ; 
 int HCLGEVF_RSS_HASH_KEY_NUM ; 
 int HCLGEVF_RSS_HASH_KEY_OFFSET ; 
 int HCLGEVF_RSS_KEY_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 int hclgevf_cmd_send (int /*<<< orphan*/ *,struct hclgevf_desc*,int) ; 
 int /*<<< orphan*/  hclgevf_cmd_setup_basic_desc (struct hclgevf_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclgevf_get_rss_hw_cfg(struct hnae3_handle *handle, u8 *hash,
				  u8 *key)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	struct hclgevf_rss_config_cmd *req;
	int lkup_times = key ? 3 : 1;
	struct hclgevf_desc desc;
	int key_offset;
	int key_size;
	int status;

	req = (struct hclgevf_rss_config_cmd *)desc.data;
	lkup_times = (lkup_times == 3) ? 3 : ((hash) ? 1 : 0);

	for (key_offset = 0; key_offset < lkup_times; key_offset++) {
		hclgevf_cmd_setup_basic_desc(&desc,
					     HCLGEVF_OPC_RSS_GENERIC_CONFIG,
					     true);
		req->hash_config |= (key_offset << HCLGEVF_RSS_HASH_KEY_OFFSET);

		status = hclgevf_cmd_send(&hdev->hw, &desc, 1);
		if (status) {
			dev_err(&hdev->pdev->dev,
				"failed to get hardware RSS cfg, status = %d\n",
				status);
			return status;
		}

		if (key_offset == 2)
			key_size =
			HCLGEVF_RSS_KEY_SIZE - HCLGEVF_RSS_HASH_KEY_NUM * 2;
		else
			key_size = HCLGEVF_RSS_HASH_KEY_NUM;

		if (key)
			memcpy(key + key_offset * HCLGEVF_RSS_HASH_KEY_NUM,
			       req->hash_key,
			       key_size);
	}

	if (hash) {
		if ((req->hash_config & 0xf) == HCLGEVF_RSS_HASH_ALGO_TOEPLITZ)
			*hash = ETH_RSS_HASH_TOP;
		else
			*hash = ETH_RSS_HASH_UNKNOWN;
	}

	return 0;
}