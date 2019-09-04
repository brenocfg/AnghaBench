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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fm10k_hw {int dummy; } ;
struct fm10k_intfc {int* reta; struct fm10k_hw hw; TYPE_1__* ring_feature; } ;
struct TYPE_2__ {int /*<<< orphan*/  indices; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_RETA (int /*<<< orphan*/ ,int) ; 
 int FM10K_RETA_SIZE ; 
 size_t RING_F_RSS ; 
 int ethtool_rxfh_indir_default (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,int /*<<< orphan*/ ,int) ; 

void fm10k_write_reta(struct fm10k_intfc *interface, const u32 *indir)
{
	u16 rss_i = interface->ring_feature[RING_F_RSS].indices;
	struct fm10k_hw *hw = &interface->hw;
	u32 table[4];
	int i, j;

	/* record entries to reta table */
	for (i = 0; i < FM10K_RETA_SIZE; i++) {
		u32 reta, n;

		/* generate a new table if we weren't given one */
		for (j = 0; j < 4; j++) {
			if (indir)
				n = indir[4 * i + j];
			else
				n = ethtool_rxfh_indir_default(4 * i + j,
							       rss_i);

			table[j] = n;
		}

		reta = table[0] |
			(table[1] << 8) |
			(table[2] << 16) |
			(table[3] << 24);

		if (interface->reta[i] == reta)
			continue;

		interface->reta[i] = reta;
		fm10k_write_reg(hw, FM10K_RETA(0, i), reta);
	}
}