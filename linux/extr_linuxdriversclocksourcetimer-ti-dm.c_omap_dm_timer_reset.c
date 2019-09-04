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
struct omap_dm_timer {int revision; scalar_t__ posted; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  OMAP_TIMER_IF_CTRL_REG ; 
 int /*<<< orphan*/  OMAP_TIMER_OCP_CFG_OFFSET ; 
 int /*<<< orphan*/  OMAP_TIMER_V1_SYS_STAT_OFFSET ; 
 int __omap_dm_timer_read (struct omap_dm_timer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __omap_dm_timer_write (struct omap_dm_timer*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  omap_dm_timer_write_reg (struct omap_dm_timer*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int omap_dm_timer_reset(struct omap_dm_timer *timer)
{
	u32 l, timeout = 100000;

	if (timer->revision != 1)
		return -EINVAL;

	omap_dm_timer_write_reg(timer, OMAP_TIMER_IF_CTRL_REG, 0x06);

	do {
		l = __omap_dm_timer_read(timer,
					 OMAP_TIMER_V1_SYS_STAT_OFFSET, 0);
	} while (!l && timeout--);

	if (!timeout) {
		dev_err(&timer->pdev->dev, "Timer failed to reset\n");
		return -ETIMEDOUT;
	}

	/* Configure timer for smart-idle mode */
	l = __omap_dm_timer_read(timer, OMAP_TIMER_OCP_CFG_OFFSET, 0);
	l |= 0x2 << 0x3;
	__omap_dm_timer_write(timer, OMAP_TIMER_OCP_CFG_OFFSET, l, 0);

	timer->posted = 0;

	return 0;
}