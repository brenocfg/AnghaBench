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
struct bnad_tx_info {int /*<<< orphan*/  tx; } ;
struct bnad {int /*<<< orphan*/  tx_coalescing_timeo; struct bnad_tx_info* tx_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  bna_tx_coalescing_timeo_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bnad_tx_coalescing_timeo_set(struct bnad *bnad)
{
	struct bnad_tx_info *tx_info;

	tx_info = &bnad->tx_info[0];
	if (!tx_info->tx)
		return;

	bna_tx_coalescing_timeo_set(tx_info->tx, bnad->tx_coalescing_timeo);
}