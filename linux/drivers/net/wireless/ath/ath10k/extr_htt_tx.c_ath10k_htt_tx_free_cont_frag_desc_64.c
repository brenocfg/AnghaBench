#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct htt_msdu_ext_desc_64 {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * vaddr_desc_64; int /*<<< orphan*/  paddr; } ;
struct ath10k_htt {int max_num_pending_tx; TYPE_2__ frag_desc; TYPE_1__* ar; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_htt_tx_free_cont_frag_desc_64(struct ath10k_htt *htt)
{
	size_t size;

	if (!htt->frag_desc.vaddr_desc_64)
		return;

	size = htt->max_num_pending_tx *
			sizeof(struct htt_msdu_ext_desc_64);

	dma_free_coherent(htt->ar->dev,
			  size,
			  htt->frag_desc.vaddr_desc_64,
			  htt->frag_desc.paddr);

	htt->frag_desc.vaddr_desc_64 = NULL;
}