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
struct enetc_bdr {int bd_count; int /*<<< orphan*/ * tx_swbd; int /*<<< orphan*/ * bd_base; int /*<<< orphan*/  bd_dma_base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_free_tx_skb (struct enetc_bdr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void enetc_free_txbdr(struct enetc_bdr *txr)
{
	int size, i;

	for (i = 0; i < txr->bd_count; i++)
		enetc_free_tx_skb(txr, &txr->tx_swbd[i]);

	size = txr->bd_count * sizeof(union enetc_tx_bd);

	dma_free_coherent(txr->dev, size, txr->bd_base, txr->bd_dma_base);
	txr->bd_base = NULL;

	vfree(txr->tx_swbd);
	txr->tx_swbd = NULL;
}