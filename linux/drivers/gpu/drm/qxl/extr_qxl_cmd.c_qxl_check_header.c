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
struct qxl_ring_header {scalar_t__ prod; scalar_t__ cons; scalar_t__ num_items; scalar_t__ notify_on_cons; } ;
struct qxl_ring {int /*<<< orphan*/  lock; TYPE_1__* ring; } ;
struct TYPE_2__ {struct qxl_ring_header header; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int qxl_check_header(struct qxl_ring *ring)
{
	int ret;
	struct qxl_ring_header *header = &(ring->ring->header);
	unsigned long flags;

	spin_lock_irqsave(&ring->lock, flags);
	ret = header->prod - header->cons < header->num_items;
	if (ret == 0)
		header->notify_on_cons = header->cons + 1;
	spin_unlock_irqrestore(&ring->lock, flags);
	return ret;
}