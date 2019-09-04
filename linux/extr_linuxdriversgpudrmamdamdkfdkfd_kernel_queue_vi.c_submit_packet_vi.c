#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kernel_queue {int /*<<< orphan*/  pending_wptr; TYPE_2__* queue; int /*<<< orphan*/ * wptr_kernel; } ;
struct TYPE_3__ {int /*<<< orphan*/  doorbell_ptr; } ;
struct TYPE_4__ {TYPE_1__ properties; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_kernel_doorbell (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void submit_packet_vi(struct kernel_queue *kq)
{
	*kq->wptr_kernel = kq->pending_wptr;
	write_kernel_doorbell(kq->queue->properties.doorbell_ptr,
				kq->pending_wptr);
}