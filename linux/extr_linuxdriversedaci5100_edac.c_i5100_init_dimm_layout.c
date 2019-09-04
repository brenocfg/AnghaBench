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
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct mem_ctl_info {struct i5100_priv* pvt_info; } ;
struct i5100_priv {int** dimm_numrank; } ;

/* Variables and functions */
 int I5100_CHANNELS ; 
 int I5100_MAX_DIMM_SLOTS_PER_CHAN ; 
 int /*<<< orphan*/  i5100_init_dimm_csmap (struct mem_ctl_info*) ; 
 scalar_t__ i5100_read_spd_byte (struct mem_ctl_info*,int,int,int,int*) ; 

__attribute__((used)) static void i5100_init_dimm_layout(struct pci_dev *pdev,
				   struct mem_ctl_info *mci)
{
	struct i5100_priv *priv = mci->pvt_info;
	int i;

	for (i = 0; i < I5100_CHANNELS; i++) {
		int j;

		for (j = 0; j < I5100_MAX_DIMM_SLOTS_PER_CHAN; j++) {
			u8 rank;

			if (i5100_read_spd_byte(mci, i, j, 5, &rank) < 0)
				priv->dimm_numrank[i][j] = 0;
			else
				priv->dimm_numrank[i][j] = (rank & 3) + 1;
		}
	}

	i5100_init_dimm_csmap(mci);
}