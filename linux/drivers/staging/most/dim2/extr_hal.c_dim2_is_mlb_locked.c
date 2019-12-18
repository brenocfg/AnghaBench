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
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* dim2; } ;
struct TYPE_3__ {int /*<<< orphan*/  MLBC0; int /*<<< orphan*/  MLBC1; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLBC0_MLBLK_BIT ; 
 int /*<<< orphan*/  MLBC1_CLKMERR_BIT ; 
 int /*<<< orphan*/  MLBC1_LOCKERR_BIT ; 
 scalar_t__ MLBC1_NDA_MASK ; 
 int MLBC1_NDA_SHIFT ; 
 int bit_mask (int /*<<< orphan*/ ) ; 
 TYPE_2__ g ; 
 int const readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool dim2_is_mlb_locked(void)
{
	u32 const mask0 = bit_mask(MLBC0_MLBLK_BIT);
	u32 const mask1 = bit_mask(MLBC1_CLKMERR_BIT) |
			  bit_mask(MLBC1_LOCKERR_BIT);
	u32 const c1 = readl(&g.dim2->MLBC1);
	u32 const nda_mask = (u32)MLBC1_NDA_MASK << MLBC1_NDA_SHIFT;

	writel(c1 & nda_mask, &g.dim2->MLBC1);
	return (readl(&g.dim2->MLBC1) & mask1) == 0 &&
	       (readl(&g.dim2->MLBC0) & mask0) != 0;
}