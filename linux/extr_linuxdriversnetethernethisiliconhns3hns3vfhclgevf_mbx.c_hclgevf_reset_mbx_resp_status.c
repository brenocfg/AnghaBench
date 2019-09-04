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
struct TYPE_2__ {int received_resp; int /*<<< orphan*/  additional_info; scalar_t__ resp_status; scalar_t__ origin_mbx_msg; } ;
struct hclgevf_dev {TYPE_1__ mbx_resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_MBX_MAX_RESP_DATA_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclgevf_reset_mbx_resp_status(struct hclgevf_dev *hdev)
{
	/* this function should be called with mbx_resp.mbx_mutex held
	 * to prtect the received_response from race condition
	 */
	hdev->mbx_resp.received_resp  = false;
	hdev->mbx_resp.origin_mbx_msg = 0;
	hdev->mbx_resp.resp_status    = 0;
	memset(hdev->mbx_resp.additional_info, 0, HCLGE_MBX_MAX_RESP_DATA_SIZE);
}