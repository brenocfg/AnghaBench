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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {unsigned int tldr; unsigned int tcrr; int /*<<< orphan*/  tclr; } ;
struct omap_dm_timer {TYPE_1__ context; int /*<<< orphan*/  posted; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OMAP_TIMER_CTRL_AR ; 
 int /*<<< orphan*/  OMAP_TIMER_CTRL_REG ; 
 int /*<<< orphan*/  OMAP_TIMER_CTRL_ST ; 
 int /*<<< orphan*/  OMAP_TIMER_LOAD_REG ; 
 int /*<<< orphan*/  __omap_dm_timer_load_start (struct omap_dm_timer*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dm_timer_enable (struct omap_dm_timer*) ; 
 int /*<<< orphan*/  omap_dm_timer_read_reg (struct omap_dm_timer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dm_timer_write_reg (struct omap_dm_timer*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

int omap_dm_timer_set_load_start(struct omap_dm_timer *timer, int autoreload,
                            unsigned int load)
{
	u32 l;

	if (unlikely(!timer))
		return -EINVAL;

	omap_dm_timer_enable(timer);

	l = omap_dm_timer_read_reg(timer, OMAP_TIMER_CTRL_REG);
	if (autoreload) {
		l |= OMAP_TIMER_CTRL_AR;
		omap_dm_timer_write_reg(timer, OMAP_TIMER_LOAD_REG, load);
	} else {
		l &= ~OMAP_TIMER_CTRL_AR;
	}
	l |= OMAP_TIMER_CTRL_ST;

	__omap_dm_timer_load_start(timer, l, load, timer->posted);

	/* Save the context */
	timer->context.tclr = l;
	timer->context.tldr = load;
	timer->context.tcrr = load;
	return 0;
}