#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct s_smt_tx_queue {void* tx_bmu_dsc; void* tx_bmu_ctl; } ;
struct TYPE_5__ {struct s_smt_tx_queue* tx_q; struct s_smt_tx_queue** tx; } ;
struct TYPE_6__ {TYPE_2__ fp; } ;
struct TYPE_4__ {int /*<<< orphan*/  sync_bw; } ;
struct s_smc {TYPE_3__ hw; TYPE_1__ ess; } ;
typedef  void* HW_PTR ;

/* Variables and functions */
 scalar_t__ ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B0_XA_CSR ; 
 int /*<<< orphan*/  B0_XS_CSR ; 
 int /*<<< orphan*/  B5_XA_DA ; 
 int /*<<< orphan*/  B5_XS_DA ; 
 size_t QUEUE_A0 ; 
 size_t QUEUE_S ; 
 int /*<<< orphan*/  llc_recover_tx (struct s_smc*) ; 
 int /*<<< orphan*/  set_formac_tsync (struct s_smc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_tx(struct s_smc *smc)
{
	struct s_smt_tx_queue	*queue ;

	/*
	 * init all tx data structures for the synchronous queue
	 */
	smc->hw.fp.tx[QUEUE_S] = queue = &smc->hw.fp.tx_q[QUEUE_S] ;
	queue->tx_bmu_ctl = (HW_PTR) ADDR(B0_XS_CSR) ;
	queue->tx_bmu_dsc = (HW_PTR) ADDR(B5_XS_DA) ;

#ifdef ESS
	set_formac_tsync(smc,smc->ess.sync_bw) ;
#endif

	/*
	 * init all tx data structures for the asynchronous queue 0
	 */
	smc->hw.fp.tx[QUEUE_A0] = queue = &smc->hw.fp.tx_q[QUEUE_A0] ;
	queue->tx_bmu_ctl = (HW_PTR) ADDR(B0_XA_CSR) ;
	queue->tx_bmu_dsc = (HW_PTR) ADDR(B5_XA_DA) ;


	llc_recover_tx(smc) ;
}