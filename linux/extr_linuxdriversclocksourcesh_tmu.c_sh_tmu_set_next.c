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
struct sh_tmu_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCNT ; 
 int /*<<< orphan*/  TCOR ; 
 int /*<<< orphan*/  TCR ; 
 unsigned long TCR_TPSC_CLK4 ; 
 unsigned long TCR_UNIE ; 
 int /*<<< orphan*/  sh_tmu_read (struct sh_tmu_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_tmu_start_stop_ch (struct sh_tmu_channel*,int) ; 
 int /*<<< orphan*/  sh_tmu_write (struct sh_tmu_channel*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void sh_tmu_set_next(struct sh_tmu_channel *ch, unsigned long delta,
			    int periodic)
{
	/* stop timer */
	sh_tmu_start_stop_ch(ch, 0);

	/* acknowledge interrupt */
	sh_tmu_read(ch, TCR);

	/* enable interrupt */
	sh_tmu_write(ch, TCR, TCR_UNIE | TCR_TPSC_CLK4);

	/* reload delta value in case of periodic timer */
	if (periodic)
		sh_tmu_write(ch, TCOR, delta);
	else
		sh_tmu_write(ch, TCOR, 0xffffffff);

	sh_tmu_write(ch, TCNT, delta);

	/* start timer */
	sh_tmu_start_stop_ch(ch, 1);
}