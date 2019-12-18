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
struct bna_rxp {int /*<<< orphan*/  qe; } ;
struct bna_rx_mod {int /*<<< orphan*/  rxp_free_count; int /*<<< orphan*/  rxp_free_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bna_rxp_put(struct bna_rx_mod *rx_mod, struct bna_rxp *rxp)
{
	list_add_tail(&rxp->qe, &rx_mod->rxp_free_q);
	rx_mod->rxp_free_count++;
}