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
struct nvme_tcp_request {int /*<<< orphan*/  pdu; } ;
struct nvme_tcp_ctrl {struct nvme_tcp_request async_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  page_frag_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvme_tcp_free_async_req(struct nvme_tcp_ctrl *ctrl)
{
	struct nvme_tcp_request *async = &ctrl->async_req;

	page_frag_free(async->pdu);
}