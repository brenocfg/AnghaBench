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
struct bnad {int num_txq_per_tx; int num_tx; int cfg_flags; int num_rxp_per_rx; } ;

/* Variables and functions */
 int BNAD_CF_MSIX ; 
 int BNAD_MAILBOX_MSIX_VECTORS ; 
 int bnad_rxqs_per_cq ; 

__attribute__((used)) static void
bnad_q_num_adjust(struct bnad *bnad, int msix_vectors, int temp)
{
	bnad->num_txq_per_tx = 1;
	if ((msix_vectors >= (bnad->num_tx * bnad->num_txq_per_tx)  +
	     bnad_rxqs_per_cq + BNAD_MAILBOX_MSIX_VECTORS) &&
	    (bnad->cfg_flags & BNAD_CF_MSIX)) {
		bnad->num_rxp_per_rx = msix_vectors -
			(bnad->num_tx * bnad->num_txq_per_tx) -
			BNAD_MAILBOX_MSIX_VECTORS;
	} else
		bnad->num_rxp_per_rx = 1;
}