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
struct mem_ctl_info {struct i5100_priv* pvt_info; } ;
struct i5100_priv {int** dimm_numrank; int** dimm_csmap; } ;

/* Variables and functions */
 int I5100_MAX_DIMM_SLOTS_PER_CHAN ; 

__attribute__((used)) static int i5100_rank_to_slot(const struct mem_ctl_info *mci,
			      int chan, int rank)
{
	const struct i5100_priv *priv = mci->pvt_info;
	int i;

	for (i = 0; i < I5100_MAX_DIMM_SLOTS_PER_CHAN; i++) {
		int j;
		const int numrank = priv->dimm_numrank[chan][i];

		for (j = 0; j < numrank; j++)
			if (priv->dimm_csmap[i][j] == rank)
				return i * 2 + chan;
	}

	return -1;
}