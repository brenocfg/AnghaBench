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
struct bna_tx {TYPE_1__* bna; int /*<<< orphan*/  (* tx_cleanup_cbfn ) (int /*<<< orphan*/ ,struct bna_tx*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  bnad; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct bna_tx*) ; 

__attribute__((used)) static void
bna_tx_sm_prio_cleanup_wait_entry(struct bna_tx *tx)
{
	tx->tx_cleanup_cbfn(tx->bna->bnad, tx);
}