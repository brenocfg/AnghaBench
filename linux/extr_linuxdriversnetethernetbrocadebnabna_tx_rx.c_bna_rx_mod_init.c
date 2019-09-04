#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bna_rxq {int /*<<< orphan*/  qe; } ;
struct bna_rxp {int /*<<< orphan*/  qe; } ;
struct bna_rx_mod {scalar_t__ rxq_free_count; int /*<<< orphan*/  rxq_free_q; struct bna_rxq* rxq; scalar_t__ rxp_free_count; int /*<<< orphan*/  rxp_free_q; struct bna_rxp* rxp; scalar_t__ rx_free_count; int /*<<< orphan*/  rx_free_q; struct bna_rx* rx; int /*<<< orphan*/  rx_active_q; scalar_t__ flags; struct bna* bna; } ;
struct bna_rx {int rid; int /*<<< orphan*/  qe; int /*<<< orphan*/ * stop_cbarg; int /*<<< orphan*/ * stop_cbfn; int /*<<< orphan*/ * bna; int /*<<< orphan*/  rxp_q; } ;
struct TYPE_7__ {TYPE_1__* mdl; } ;
struct TYPE_8__ {TYPE_2__ mem_info; } ;
struct bna_res_info {TYPE_3__ res_u; } ;
struct TYPE_9__ {int num_rxp; } ;
struct TYPE_10__ {TYPE_4__ attr; } ;
struct bna {TYPE_5__ ioceth; } ;
struct TYPE_6__ {scalar_t__ kva; } ;

/* Variables and functions */
 size_t BNA_MOD_RES_MEM_T_RXP_ARRAY ; 
 size_t BNA_MOD_RES_MEM_T_RXQ_ARRAY ; 
 size_t BNA_MOD_RES_MEM_T_RX_ARRAY ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void bna_rx_mod_init(struct bna_rx_mod *rx_mod, struct bna *bna,
			struct bna_res_info *res_info)
{
	int	index;
	struct bna_rx *rx_ptr;
	struct bna_rxp *rxp_ptr;
	struct bna_rxq *rxq_ptr;

	rx_mod->bna = bna;
	rx_mod->flags = 0;

	rx_mod->rx = (struct bna_rx *)
		res_info[BNA_MOD_RES_MEM_T_RX_ARRAY].res_u.mem_info.mdl[0].kva;
	rx_mod->rxp = (struct bna_rxp *)
		res_info[BNA_MOD_RES_MEM_T_RXP_ARRAY].res_u.mem_info.mdl[0].kva;
	rx_mod->rxq = (struct bna_rxq *)
		res_info[BNA_MOD_RES_MEM_T_RXQ_ARRAY].res_u.mem_info.mdl[0].kva;

	/* Initialize the queues */
	INIT_LIST_HEAD(&rx_mod->rx_free_q);
	rx_mod->rx_free_count = 0;
	INIT_LIST_HEAD(&rx_mod->rxq_free_q);
	rx_mod->rxq_free_count = 0;
	INIT_LIST_HEAD(&rx_mod->rxp_free_q);
	rx_mod->rxp_free_count = 0;
	INIT_LIST_HEAD(&rx_mod->rx_active_q);

	/* Build RX queues */
	for (index = 0; index < bna->ioceth.attr.num_rxp; index++) {
		rx_ptr = &rx_mod->rx[index];

		INIT_LIST_HEAD(&rx_ptr->rxp_q);
		rx_ptr->bna = NULL;
		rx_ptr->rid = index;
		rx_ptr->stop_cbfn = NULL;
		rx_ptr->stop_cbarg = NULL;

		list_add_tail(&rx_ptr->qe, &rx_mod->rx_free_q);
		rx_mod->rx_free_count++;
	}

	/* build RX-path queue */
	for (index = 0; index < bna->ioceth.attr.num_rxp; index++) {
		rxp_ptr = &rx_mod->rxp[index];
		list_add_tail(&rxp_ptr->qe, &rx_mod->rxp_free_q);
		rx_mod->rxp_free_count++;
	}

	/* build RXQ queue */
	for (index = 0; index < (bna->ioceth.attr.num_rxp * 2); index++) {
		rxq_ptr = &rx_mod->rxq[index];
		list_add_tail(&rxq_ptr->qe, &rx_mod->rxq_free_q);
		rx_mod->rxq_free_count++;
	}
}