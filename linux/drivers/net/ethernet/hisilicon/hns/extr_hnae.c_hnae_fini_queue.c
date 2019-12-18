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
struct hnae_queue {int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  tx_ring; TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* fini_queue ) (struct hnae_queue*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  hnae_fini_ring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hnae_queue*) ; 

__attribute__((used)) static void hnae_fini_queue(struct hnae_queue *q)
{
	if (q->dev->ops->fini_queue)
		q->dev->ops->fini_queue(q);

	hnae_fini_ring(&q->tx_ring);
	hnae_fini_ring(&q->rx_ring);
}