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
typedef  int /*<<< orphan*/  u32 ;
struct ath10k_ce {int /*<<< orphan*/  paddr_rri; int /*<<< orphan*/  vaddr_rri; } ;
struct ath10k {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CE_COUNT ; 
 struct ath10k_ce* ath10k_ce_priv (struct ath10k*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ath10k_ce_free_rri(struct ath10k *ar)
{
	struct ath10k_ce *ce = ath10k_ce_priv(ar);

	dma_free_coherent(ar->dev, (CE_COUNT * sizeof(u32)),
			  ce->vaddr_rri,
			  ce->paddr_rri);
}