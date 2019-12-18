#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvme_ctrl {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pdu; } ;
struct TYPE_5__ {TYPE_1__ async_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_tcp_free_async_req (TYPE_2__*) ; 
 int /*<<< orphan*/  nvme_tcp_free_queue (struct nvme_ctrl*,int /*<<< orphan*/ ) ; 
 TYPE_2__* to_tcp_ctrl (struct nvme_ctrl*) ; 

__attribute__((used)) static void nvme_tcp_free_admin_queue(struct nvme_ctrl *ctrl)
{
	if (to_tcp_ctrl(ctrl)->async_req.pdu) {
		nvme_tcp_free_async_req(to_tcp_ctrl(ctrl));
		to_tcp_ctrl(ctrl)->async_req.pdu = NULL;
	}

	nvme_tcp_free_queue(ctrl, 0);
}