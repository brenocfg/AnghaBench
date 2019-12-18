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
struct bna_res_info {int dummy; } ;
struct bna {int /*<<< orphan*/  mod_flags; void* promisc_rid; void* default_mode_rid; int /*<<< orphan*/  mcam_mod; int /*<<< orphan*/  ucam_mod; int /*<<< orphan*/  rx_mod; int /*<<< orphan*/  tx_mod; } ;

/* Variables and functions */
 void* BFI_INVALID_RID ; 
 int /*<<< orphan*/  BNA_MOD_F_INIT_DONE ; 
 int /*<<< orphan*/  bna_mcam_mod_init (int /*<<< orphan*/ *,struct bna*,struct bna_res_info*) ; 
 int /*<<< orphan*/  bna_rx_mod_init (int /*<<< orphan*/ *,struct bna*,struct bna_res_info*) ; 
 int /*<<< orphan*/  bna_tx_mod_init (int /*<<< orphan*/ *,struct bna*,struct bna_res_info*) ; 
 int /*<<< orphan*/  bna_ucam_mod_init (int /*<<< orphan*/ *,struct bna*,struct bna_res_info*) ; 

void
bna_mod_init(struct bna *bna, struct bna_res_info *res_info)
{
	bna_tx_mod_init(&bna->tx_mod, bna, res_info);

	bna_rx_mod_init(&bna->rx_mod, bna, res_info);

	bna_ucam_mod_init(&bna->ucam_mod, bna, res_info);

	bna_mcam_mod_init(&bna->mcam_mod, bna, res_info);

	bna->default_mode_rid = BFI_INVALID_RID;
	bna->promisc_rid = BFI_INVALID_RID;

	bna->mod_flags |= BNA_MOD_F_INIT_DONE;
}