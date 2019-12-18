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
typedef  int /*<<< orphan*/  u32 ;
struct ssb_chipcommon {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSB_CHIPCO_PLLCTL_ADDR ; 
 int /*<<< orphan*/  SSB_CHIPCO_PLLCTL_DATA ; 
 int /*<<< orphan*/  chipco_write32 (struct ssb_chipcommon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ssb_chipco_pll_write(struct ssb_chipcommon *cc,
				 u32 offset, u32 value)
{
	chipco_write32(cc, SSB_CHIPCO_PLLCTL_ADDR, offset);
	chipco_write32(cc, SSB_CHIPCO_PLLCTL_DATA, value);
}