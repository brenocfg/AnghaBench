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
typedef  int /*<<< orphan*/  u16 ;
struct hnae3_handle {int dummy; } ;
struct hclgevf_dev {int dummy; } ;
typedef  int /*<<< orphan*/  queue_id ;
typedef  int /*<<< orphan*/  msg_data ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_MBX_QUEUE_RESET ; 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 int hclgevf_send_mbx_msg (struct hclgevf_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hclgevf_tqp_enable (struct hclgevf_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hclgevf_reset_tqp(struct hnae3_handle *handle, u16 queue_id)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	u8 msg_data[2];
	int ret;

	memcpy(msg_data, &queue_id, sizeof(queue_id));

	/* disable vf queue before send queue reset msg to PF */
	ret = hclgevf_tqp_enable(hdev, queue_id, 0, false);
	if (ret)
		return ret;

	return hclgevf_send_mbx_msg(hdev, HCLGE_MBX_QUEUE_RESET, 0, msg_data,
				    sizeof(msg_data), true, NULL, 0);
}