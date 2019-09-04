#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_pause; } ;
struct TYPE_7__ {int /*<<< orphan*/  num_entries; } ;
struct bfi_enet_set_pause_req {TYPE_3__ mh; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_pause; } ;
struct bna_enet {int /*<<< orphan*/  msgq_cmd; TYPE_2__* bna; TYPE_1__ pause_config; struct bfi_enet_set_pause_req pause_req; } ;
struct TYPE_6__ {int /*<<< orphan*/  msgq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_ENET_H2I_SET_PAUSE_REQ ; 
 int /*<<< orphan*/  BFI_MC_ENET ; 
 int /*<<< orphan*/  bfa_msgq_cmd_post (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_msgq_cmd_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_3__*) ; 
 int /*<<< orphan*/  bfi_msgq_mhdr_set (TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_msgq_num_cmd_entries (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bna_bfi_pause_set(struct bna_enet *enet)
{
	struct bfi_enet_set_pause_req *pause_req = &enet->pause_req;

	bfi_msgq_mhdr_set(pause_req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_SET_PAUSE_REQ, 0, 0);
	pause_req->mh.num_entries = htons(
	bfi_msgq_num_cmd_entries(sizeof(struct bfi_enet_set_pause_req)));
	pause_req->tx_pause = enet->pause_config.tx_pause;
	pause_req->rx_pause = enet->pause_config.rx_pause;

	bfa_msgq_cmd_set(&enet->msgq_cmd, NULL, NULL,
		sizeof(struct bfi_enet_set_pause_req), &pause_req->mh);
	bfa_msgq_cmd_post(&enet->bna->msgq, &enet->msgq_cmd);
}