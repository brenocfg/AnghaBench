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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct rvu_pfvf {int rxvlan; scalar_t__ minlen; scalar_t__ maxlen; } ;
struct rvu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int nix_update_bcast_mce_list (struct rvu*,int /*<<< orphan*/ ,int) ; 
 struct rvu_pfvf* rvu_get_pfvf (struct rvu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_npc_disable_mcam_entries (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nix_interface_deinit(struct rvu *rvu, u16 pcifunc, u8 nixlf)
{
	struct rvu_pfvf *pfvf = rvu_get_pfvf(rvu, pcifunc);
	int err;

	pfvf->maxlen = 0;
	pfvf->minlen = 0;
	pfvf->rxvlan = false;

	/* Remove this PF_FUNC from bcast pkt replication list */
	err = nix_update_bcast_mce_list(rvu, pcifunc, false);
	if (err) {
		dev_err(rvu->dev,
			"Bcast list, failed to disable PF_FUNC 0x%x\n",
			pcifunc);
	}

	/* Free and disable any MCAM entries used by this NIX LF */
	rvu_npc_disable_mcam_entries(rvu, pcifunc, nixlf);
}