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
typedef  int u32 ;
struct igc_hw {int dummy; } ;
struct igc_adapter {int* rss_indir_tbl; struct igc_hw hw; } ;

/* Variables and functions */
 int IGC_RETA (int /*<<< orphan*/ ) ; 
 int IGC_RETA_SIZE ; 
 int /*<<< orphan*/  wr32 (int,int) ; 

void igc_write_rss_indir_tbl(struct igc_adapter *adapter)
{
	struct igc_hw *hw = &adapter->hw;
	u32 reg = IGC_RETA(0);
	u32 shift = 0;
	int i = 0;

	while (i < IGC_RETA_SIZE) {
		u32 val = 0;
		int j;

		for (j = 3; j >= 0; j--) {
			val <<= 8;
			val |= adapter->rss_indir_tbl[i + j];
		}

		wr32(reg, val << shift);
		reg += 4;
		i += 4;
	}
}