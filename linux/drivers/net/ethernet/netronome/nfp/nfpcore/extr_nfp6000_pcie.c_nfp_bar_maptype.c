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
struct nfp_bar {int /*<<< orphan*/  barcfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_PCIE_BAR_PCIE2CPP_MapType_of (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 nfp_bar_maptype(struct nfp_bar *bar)
{
	return NFP_PCIE_BAR_PCIE2CPP_MapType_of(bar->barcfg);
}