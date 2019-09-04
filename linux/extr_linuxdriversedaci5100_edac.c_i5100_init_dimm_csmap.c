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
struct i5100_priv {int** dimm_csmap; int ranksperchan; } ;

/* Variables and functions */
 int I5100_MAX_DIMM_SLOTS_PER_CHAN ; 
 int I5100_MAX_RANKS_PER_DIMM ; 

__attribute__((used)) static void i5100_init_dimm_csmap(struct mem_ctl_info *mci)
{
	struct i5100_priv *priv = mci->pvt_info;
	int i;

	for (i = 0; i < I5100_MAX_DIMM_SLOTS_PER_CHAN; i++) {
		int j;

		for (j = 0; j < I5100_MAX_RANKS_PER_DIMM; j++)
			priv->dimm_csmap[i][j] = -1; /* default NC */
	}

	/* only 2 chip selects per slot... */
	if (priv->ranksperchan == 4) {
		priv->dimm_csmap[0][0] = 0;
		priv->dimm_csmap[0][1] = 3;
		priv->dimm_csmap[1][0] = 1;
		priv->dimm_csmap[1][1] = 2;
		priv->dimm_csmap[2][0] = 2;
		priv->dimm_csmap[3][0] = 3;
	} else {
		priv->dimm_csmap[0][0] = 0;
		priv->dimm_csmap[0][1] = 1;
		priv->dimm_csmap[1][0] = 2;
		priv->dimm_csmap[1][1] = 3;
		priv->dimm_csmap[2][0] = 4;
		priv->dimm_csmap[2][1] = 5;
	}
}