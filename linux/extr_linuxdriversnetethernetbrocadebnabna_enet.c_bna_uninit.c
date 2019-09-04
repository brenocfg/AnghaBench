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
struct bna {int mod_flags; int /*<<< orphan*/ * bnad; int /*<<< orphan*/  ioceth; int /*<<< orphan*/  enet; int /*<<< orphan*/  ethport; int /*<<< orphan*/  stats_mod; int /*<<< orphan*/  tx_mod; int /*<<< orphan*/  rx_mod; int /*<<< orphan*/  ucam_mod; int /*<<< orphan*/  mcam_mod; } ;

/* Variables and functions */
 int BNA_MOD_F_INIT_DONE ; 
 int /*<<< orphan*/  bna_enet_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bna_ethport_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bna_ioceth_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bna_mcam_mod_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bna_rx_mod_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bna_stats_mod_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bna_tx_mod_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bna_ucam_mod_uninit (int /*<<< orphan*/ *) ; 

void
bna_uninit(struct bna *bna)
{
	if (bna->mod_flags & BNA_MOD_F_INIT_DONE) {
		bna_mcam_mod_uninit(&bna->mcam_mod);
		bna_ucam_mod_uninit(&bna->ucam_mod);
		bna_rx_mod_uninit(&bna->rx_mod);
		bna_tx_mod_uninit(&bna->tx_mod);
		bna->mod_flags &= ~BNA_MOD_F_INIT_DONE;
	}

	bna_stats_mod_uninit(&bna->stats_mod);
	bna_ethport_uninit(&bna->ethport);
	bna_enet_uninit(&bna->enet);

	bna_ioceth_uninit(&bna->ioceth);

	bna->bnad = NULL;
}