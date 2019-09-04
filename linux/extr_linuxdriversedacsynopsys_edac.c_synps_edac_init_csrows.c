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
struct synps_edac_priv {int /*<<< orphan*/  baseaddr; } ;
struct mem_ctl_info {int nr_csrows; struct csrow_info** csrows; struct synps_edac_priv* pvt_info; } ;
struct dimm_info {int nr_pages; int /*<<< orphan*/  dtype; int /*<<< orphan*/  grain; int /*<<< orphan*/  mtype; int /*<<< orphan*/  edac_mode; } ;
struct csrow_info {int nr_channels; TYPE_1__** channels; } ;
struct TYPE_2__ {struct dimm_info* dimm; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_FLAG_SECDED ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  SYNPS_EDAC_ERR_GRAIN ; 
 int /*<<< orphan*/  synps_edac_get_dtype (int /*<<< orphan*/ ) ; 
 int synps_edac_get_memsize () ; 
 int /*<<< orphan*/  synps_edac_get_mtype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int synps_edac_init_csrows(struct mem_ctl_info *mci)
{
	struct csrow_info *csi;
	struct dimm_info *dimm;
	struct synps_edac_priv *priv = mci->pvt_info;
	u32 size;
	int row, j;

	for (row = 0; row < mci->nr_csrows; row++) {
		csi = mci->csrows[row];
		size = synps_edac_get_memsize();

		for (j = 0; j < csi->nr_channels; j++) {
			dimm            = csi->channels[j]->dimm;
			dimm->edac_mode = EDAC_FLAG_SECDED;
			dimm->mtype     = synps_edac_get_mtype(priv->baseaddr);
			dimm->nr_pages  = (size >> PAGE_SHIFT) / csi->nr_channels;
			dimm->grain     = SYNPS_EDAC_ERR_GRAIN;
			dimm->dtype     = synps_edac_get_dtype(priv->baseaddr);
		}
	}

	return 0;
}