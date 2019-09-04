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
typedef  int u32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int BCM63XX_TIMER_COUNT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TIMER_IRQSTAT_REG ; 
 int TIMER_IRQSTAT_TIMER_CAUSE (int) ; 
 int bcm_timer_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_timer_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 TYPE_1__* timer_data ; 
 int /*<<< orphan*/  timer_data_lock ; 
 int /*<<< orphan*/  timer_reg_lock ; 

__attribute__((used)) static irqreturn_t timer_interrupt(int irq, void *dev_id)
{
	u32 stat;
	int i;

	raw_spin_lock(&timer_reg_lock);
	stat = bcm_timer_readl(TIMER_IRQSTAT_REG);
	bcm_timer_writel(stat, TIMER_IRQSTAT_REG);
	raw_spin_unlock(&timer_reg_lock);

	for (i = 0; i < BCM63XX_TIMER_COUNT; i++) {
		if (!(stat & TIMER_IRQSTAT_TIMER_CAUSE(i)))
			continue;

		raw_spin_lock(&timer_data_lock);
		if (!timer_data[i].cb) {
			raw_spin_unlock(&timer_data_lock);
			continue;
		}

		timer_data[i].cb(timer_data[i].data);
		raw_spin_unlock(&timer_data_lock);
	}

	return IRQ_HANDLED;
}