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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {scalar_t__ mode; int /*<<< orphan*/  paddr; TYPE_1__* vaddr; int /*<<< orphan*/  enabled; } ;
struct TYPE_5__ {TYPE_3__ tx_q_state; int /*<<< orphan*/  tx_lock; } ;
struct ath10k {TYPE_2__ htt; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_HTT ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ HTT_TX_MODE_SWITCH_PUSH_PULL ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __ath10k_htt_tx_txq_sync(struct ath10k *ar)
{
	u32 seq;
	size_t size;

	lockdep_assert_held(&ar->htt.tx_lock);

	if (!ar->htt.tx_q_state.enabled)
		return;

	if (ar->htt.tx_q_state.mode != HTT_TX_MODE_SWITCH_PUSH_PULL)
		return;

	seq = le32_to_cpu(ar->htt.tx_q_state.vaddr->seq);
	seq++;
	ar->htt.tx_q_state.vaddr->seq = cpu_to_le32(seq);

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt tx txq state update commit seq %u\n",
		   seq);

	size = sizeof(*ar->htt.tx_q_state.vaddr);
	dma_sync_single_for_device(ar->dev,
				   ar->htt.tx_q_state.paddr,
				   size,
				   DMA_TO_DEVICE);
}