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
struct hclgevf_dev {int dummy; } ;
typedef  int /*<<< orphan*/  send_msg ;
typedef  int /*<<< orphan*/  resp_msg ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_ADVERTISING ; 
 int /*<<< orphan*/  HCLGEVF_SUPPORTED ; 
 int /*<<< orphan*/  HCLGE_MBX_GET_LINK_MODE ; 
 int /*<<< orphan*/  hclgevf_send_mbx_msg (struct hclgevf_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void hclgevf_update_link_mode(struct hclgevf_dev *hdev)
{
#define HCLGEVF_ADVERTISING 0
#define HCLGEVF_SUPPORTED   1
	u8 send_msg;
	u8 resp_msg;

	send_msg = HCLGEVF_ADVERTISING;
	hclgevf_send_mbx_msg(hdev, HCLGE_MBX_GET_LINK_MODE, 0,
			     &send_msg, sizeof(send_msg), false,
			     &resp_msg, sizeof(resp_msg));
	send_msg = HCLGEVF_SUPPORTED;
	hclgevf_send_mbx_msg(hdev, HCLGE_MBX_GET_LINK_MODE, 0,
			     &send_msg, sizeof(send_msg), false,
			     &resp_msg, sizeof(resp_msg));
}