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
struct dim2_hdm {size_t atx_idx; TYPE_1__* hch; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ is_initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dim_lock ; 
 int /*<<< orphan*/  dim_service_mlb_int_irq () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  try_start_dim_transfer (TYPE_1__*) ; 

__attribute__((used)) static irqreturn_t dim2_mlb_isr(int irq, void *_dev)
{
	struct dim2_hdm *dev = _dev;
	unsigned long flags;

	spin_lock_irqsave(&dim_lock, flags);
	dim_service_mlb_int_irq();
	spin_unlock_irqrestore(&dim_lock, flags);

	if (dev->atx_idx >= 0 && dev->hch[dev->atx_idx].is_initialized)
		while (!try_start_dim_transfer(dev->hch + dev->atx_idx))
			continue;

	return IRQ_HANDLED;
}