#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ucma_multicast {int /*<<< orphan*/  id; int /*<<< orphan*/  uid; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; int /*<<< orphan*/  uid; } ;
struct ucma_event {TYPE_3__ resp; struct ucma_multicast* mc; struct ucma_context* ctx; } ;
struct ucma_context {int /*<<< orphan*/  id; int /*<<< orphan*/  uid; } ;
struct TYPE_4__ {scalar_t__ private_data; } ;
struct TYPE_5__ {TYPE_1__ ud; } ;
struct rdma_cm_event {int event; TYPE_2__ param; } ;

/* Variables and functions */
#define  RDMA_CM_EVENT_MULTICAST_ERROR 129 
#define  RDMA_CM_EVENT_MULTICAST_JOIN 128 

__attribute__((used)) static void ucma_set_event_context(struct ucma_context *ctx,
				   struct rdma_cm_event *event,
				   struct ucma_event *uevent)
{
	uevent->ctx = ctx;
	switch (event->event) {
	case RDMA_CM_EVENT_MULTICAST_JOIN:
	case RDMA_CM_EVENT_MULTICAST_ERROR:
		uevent->mc = (struct ucma_multicast *)
			     event->param.ud.private_data;
		uevent->resp.uid = uevent->mc->uid;
		uevent->resp.id = uevent->mc->id;
		break;
	default:
		uevent->resp.uid = ctx->uid;
		uevent->resp.id = ctx->id;
		break;
	}
}