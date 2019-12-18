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
struct TYPE_4__ {TYPE_1__* dim2; } ;
struct TYPE_3__ {int /*<<< orphan*/  ACMR1; int /*<<< orphan*/  ACMR0; int /*<<< orphan*/  ACSR1; int /*<<< orphan*/  ACSR0; int /*<<< orphan*/  MIEN; int /*<<< orphan*/  MLBC0; } ;

/* Variables and functions */
 int MLBC0_MLBEN_BIT ; 
 int /*<<< orphan*/  dim2_clear_ctram () ; 
 TYPE_2__ g ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dim2_cleanup(void)
{
	/* disable MediaLB */
	writel(false << MLBC0_MLBEN_BIT, &g.dim2->MLBC0);

	dim2_clear_ctram();

	/* disable mlb_int interrupt */
	writel(0, &g.dim2->MIEN);

	/* clear status for all dma channels */
	writel(0xFFFFFFFF, &g.dim2->ACSR0);
	writel(0xFFFFFFFF, &g.dim2->ACSR1);

	/* mask interrupts for all channels */
	writel(0, &g.dim2->ACMR0);
	writel(0, &g.dim2->ACMR1);
}