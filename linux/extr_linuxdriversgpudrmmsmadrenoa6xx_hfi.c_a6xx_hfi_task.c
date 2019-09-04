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
typedef  scalar_t__ u32 ;
struct a6xx_hfi_queue {int dummy; } ;
struct a6xx_hfi_msg_response {int /*<<< orphan*/  header; } ;
struct a6xx_gmu {int /*<<< orphan*/  dev; struct a6xx_hfi_queue* queues; } ;
typedef  int /*<<< orphan*/  resp ;

/* Variables and functions */
 scalar_t__ HFI_F2H_MSG_ACK ; 
 scalar_t__ HFI_F2H_MSG_ERROR ; 
 scalar_t__ HFI_HEADER_ID (int /*<<< orphan*/ ) ; 
 size_t HFI_RESPONSE_QUEUE ; 
 int /*<<< orphan*/  a6xx_hfi_handle_ack (struct a6xx_gmu*,struct a6xx_hfi_msg_response*) ; 
 int /*<<< orphan*/  a6xx_hfi_handle_error (struct a6xx_gmu*,struct a6xx_hfi_msg_response*) ; 
 int a6xx_hfi_queue_read (struct a6xx_hfi_queue*,scalar_t__*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

void a6xx_hfi_task(unsigned long data)
{
	struct a6xx_gmu *gmu = (struct a6xx_gmu *) data;
	struct a6xx_hfi_queue *queue = &gmu->queues[HFI_RESPONSE_QUEUE];
	struct a6xx_hfi_msg_response resp;

	for (;;) {
		u32 id;
		int ret = a6xx_hfi_queue_read(queue, (u32 *) &resp,
			sizeof(resp) >> 2);

		/* Returns the number of bytes copied or negative on error */
		if (ret <= 0) {
			if (ret < 0)
				dev_err(gmu->dev,
					"Unable to read the HFI message queue\n");
			break;
		}

		id = HFI_HEADER_ID(resp.header);

		if (id == HFI_F2H_MSG_ACK)
			a6xx_hfi_handle_ack(gmu, &resp);
		else if (id == HFI_F2H_MSG_ERROR)
			a6xx_hfi_handle_error(gmu, &resp);
	}
}