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
typedef  int /*<<< orphan*/  uint ;
struct bnad {int cfg_flags; int num_rx; int num_tx; int num_rxp_per_rx; int /*<<< orphan*/  num_txq_per_tx; } ;

/* Variables and functions */
 int BNAD_CF_MSIX ; 
 int BNAD_MAX_RX ; 
 int BNAD_MAX_RXP_PER_RX ; 
 int /*<<< orphan*/  BNAD_TXQ_NUM ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ num_online_cpus () ; 

__attribute__((used)) static void
bnad_q_num_init(struct bnad *bnad)
{
	int rxps;

	rxps = min((uint)num_online_cpus(),
			(uint)(BNAD_MAX_RX * BNAD_MAX_RXP_PER_RX));

	if (!(bnad->cfg_flags & BNAD_CF_MSIX))
		rxps = 1;	/* INTx */

	bnad->num_rx = 1;
	bnad->num_tx = 1;
	bnad->num_rxp_per_rx = rxps;
	bnad->num_txq_per_tx = BNAD_TXQ_NUM;
}