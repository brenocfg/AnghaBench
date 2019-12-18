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
struct TYPE_2__ {int /*<<< orphan*/  (* submit_packet ) (struct kernel_queue*) ;} ;
struct kernel_queue {int* wptr_kernel; int pending_wptr; TYPE_1__ ops_asic_specific; int /*<<< orphan*/ * pq_kernel_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  stub1 (struct kernel_queue*) ; 

__attribute__((used)) static void submit_packet(struct kernel_queue *kq)
{
#ifdef DEBUG
	int i;

	for (i = *kq->wptr_kernel; i < kq->pending_wptr; i++) {
		pr_debug("0x%2X ", kq->pq_kernel_addr[i]);
		if (i % 15 == 0)
			pr_debug("\n");
	}
	pr_debug("\n");
#endif

	kq->ops_asic_specific.submit_packet(kq);
}