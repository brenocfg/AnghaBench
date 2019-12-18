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
typedef  union enetc_tx_bd {int dummy; } enetc_tx_bd ;
struct enetc_tx_swbd {int dummy; } ;
struct enetc_bdr {int bd_count; scalar_t__ next_to_use; scalar_t__ next_to_clean; int /*<<< orphan*/  tx_swbd; } ;

/* Variables and functions */
 int ENOMEM ; 
 int enetc_dma_alloc_bdr (struct enetc_bdr*,int) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vzalloc (int) ; 

__attribute__((used)) static int enetc_alloc_txbdr(struct enetc_bdr *txr)
{
	int err;

	txr->tx_swbd = vzalloc(txr->bd_count * sizeof(struct enetc_tx_swbd));
	if (!txr->tx_swbd)
		return -ENOMEM;

	err = enetc_dma_alloc_bdr(txr, sizeof(union enetc_tx_bd));
	if (err) {
		vfree(txr->tx_swbd);
		return err;
	}

	txr->next_to_clean = 0;
	txr->next_to_use = 0;

	return 0;
}