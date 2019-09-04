#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kernel_queue {int pending_wptr; int* wptr_kernel; TYPE_3__* queue; int /*<<< orphan*/ * wptr64_kernel; int /*<<< orphan*/  pending_wptr64; TYPE_2__* dev; } ;
struct TYPE_8__ {int queue_size; } ;
struct TYPE_7__ {TYPE_4__ properties; } ;
struct TYPE_6__ {TYPE_1__* device_info; } ;
struct TYPE_5__ {int doorbell_size; } ;

/* Variables and functions */

__attribute__((used)) static void rollback_packet(struct kernel_queue *kq)
{
	if (kq->dev->device_info->doorbell_size == 8) {
		kq->pending_wptr64 = *kq->wptr64_kernel;
		kq->pending_wptr = *kq->wptr_kernel %
			(kq->queue->properties.queue_size / 4);
	} else {
		kq->pending_wptr = *kq->wptr_kernel;
	}
}