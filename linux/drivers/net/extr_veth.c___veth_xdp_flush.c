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
struct veth_rq {int rx_notify_masked; int /*<<< orphan*/  xdp_napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static void __veth_xdp_flush(struct veth_rq *rq)
{
	/* Write ptr_ring before reading rx_notify_masked */
	smp_mb();
	if (!rq->rx_notify_masked) {
		rq->rx_notify_masked = true;
		napi_schedule(&rq->xdp_napi);
	}
}