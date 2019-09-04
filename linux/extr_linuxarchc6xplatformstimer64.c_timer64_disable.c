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
struct TYPE_2__ {int /*<<< orphan*/  prdlo; int /*<<< orphan*/  tcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSCR_DEVSTATE_DISABLED ; 
 int TCR_ENAMODELO_MASK ; 
 int /*<<< orphan*/  dscr_set_devstate (scalar_t__,int /*<<< orphan*/ ) ; 
 int soc_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soc_writel (int,int /*<<< orphan*/ *) ; 
 TYPE_1__* timer ; 
 scalar_t__ timer64_devstate_id ; 

__attribute__((used)) static void timer64_disable(void)
{
	/* disable timer, reset count */
	soc_writel(soc_readl(&timer->tcr) & ~TCR_ENAMODELO_MASK, &timer->tcr);
	soc_writel(0, &timer->prdlo);

	if (timer64_devstate_id >= 0)
		dscr_set_devstate(timer64_devstate_id, DSCR_DEVSTATE_DISABLED);
}