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
typedef  int u8 ;
struct TYPE_4__ {int fcnt; TYPE_1__* dim2; } ;
struct TYPE_3__ {int /*<<< orphan*/  ACTL; int /*<<< orphan*/  HCTL; int /*<<< orphan*/  HCMR1; int /*<<< orphan*/  HCMR0; int /*<<< orphan*/  MLBC0; } ;

/* Variables and functions */
 int ACTL_DMA_MODE_BIT ; 
 int ACTL_DMA_MODE_VAL_DMA_MODE_1 ; 
 int ACTL_SCE_BIT ; 
 int /*<<< orphan*/  HCTL_EN_BIT ; 
 int MLBC0_FCNT_SHIFT ; 
 int MLBC0_MLBCLK_SHIFT ; 
 int MLBC0_MLBEN_BIT ; 
 int MLBC0_MLBPEN_BIT ; 
 int bit_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dim2_cleanup () ; 
 TYPE_2__ g ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dim2_initialize(bool enable_6pin, u8 mlb_clock)
{
	dim2_cleanup();

	/* configure and enable MediaLB */
	writel(enable_6pin << MLBC0_MLBPEN_BIT |
	       mlb_clock << MLBC0_MLBCLK_SHIFT |
	       g.fcnt << MLBC0_FCNT_SHIFT |
	       true << MLBC0_MLBEN_BIT,
	       &g.dim2->MLBC0);

	/* activate all HBI channels */
	writel(0xFFFFFFFF, &g.dim2->HCMR0);
	writel(0xFFFFFFFF, &g.dim2->HCMR1);

	/* enable HBI */
	writel(bit_mask(HCTL_EN_BIT), &g.dim2->HCTL);

	/* configure DMA */
	writel(ACTL_DMA_MODE_VAL_DMA_MODE_1 << ACTL_DMA_MODE_BIT |
	       true << ACTL_SCE_BIT, &g.dim2->ACTL);
}