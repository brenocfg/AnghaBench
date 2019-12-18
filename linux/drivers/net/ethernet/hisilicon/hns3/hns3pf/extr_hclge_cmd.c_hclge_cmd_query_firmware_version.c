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
typedef  int /*<<< orphan*/  u32 ;
struct hclge_query_version_cmd {int /*<<< orphan*/  firmware; } ;
struct hclge_hw {int dummy; } ;
struct hclge_desc {scalar_t__ data; } ;
typedef  enum hclge_cmd_status { ____Placeholder_hclge_cmd_status } hclge_cmd_status ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_QUERY_FW_VER ; 
 int hclge_cmd_send (struct hclge_hw*,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum hclge_cmd_status hclge_cmd_query_firmware_version(
		struct hclge_hw *hw, u32 *version)
{
	struct hclge_query_version_cmd *resp;
	struct hclge_desc desc;
	int ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_QUERY_FW_VER, 1);
	resp = (struct hclge_query_version_cmd *)desc.data;

	ret = hclge_cmd_send(hw, &desc, 1);
	if (!ret)
		*version = le32_to_cpu(resp->firmware);

	return ret;
}