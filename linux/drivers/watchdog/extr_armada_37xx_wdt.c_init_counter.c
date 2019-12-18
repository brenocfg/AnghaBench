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
typedef  int u32 ;
struct armada_37xx_watchdog {scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ CNTR_CTRL (int) ; 
 int CNTR_CTRL_MODE_MASK ; 
 int CNTR_CTRL_PRESCALE_MASK ; 
 int CNTR_CTRL_PRESCALE_MIN ; 
 int CNTR_CTRL_PRESCALE_SHIFT ; 
 int CNTR_CTRL_TRIG_SRC_MASK ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void init_counter(struct armada_37xx_watchdog *dev, int id, u32 mode,
			 u32 trig_src)
{
	u32 reg;

	reg = readl(dev->reg + CNTR_CTRL(id));

	reg &= ~(CNTR_CTRL_MODE_MASK | CNTR_CTRL_PRESCALE_MASK |
		 CNTR_CTRL_TRIG_SRC_MASK);

	/* set mode */
	reg |= mode & CNTR_CTRL_MODE_MASK;

	/* set prescaler to the min value */
	reg |= CNTR_CTRL_PRESCALE_MIN << CNTR_CTRL_PRESCALE_SHIFT;

	/* set trigger source */
	reg |= trig_src & CNTR_CTRL_TRIG_SRC_MASK;

	writel(reg, dev->reg + CNTR_CTRL(id));
}