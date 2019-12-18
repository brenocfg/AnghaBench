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
typedef  int uint32_t ;
struct pxa930_trkball {scalar_t__ mmio_base; } ;

/* Variables and functions */
 scalar_t__ TBCR ; 
 int TBCR_TBRST ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  write_tbcr (struct pxa930_trkball*,int) ; 

__attribute__((used)) static void pxa930_trkball_disable(struct pxa930_trkball *trkball)
{
	uint32_t tbcr = __raw_readl(trkball->mmio_base + TBCR);

	/* Held in reset, gate the 32-KHz input clock off */
	write_tbcr(trkball, tbcr | TBCR_TBRST);
}