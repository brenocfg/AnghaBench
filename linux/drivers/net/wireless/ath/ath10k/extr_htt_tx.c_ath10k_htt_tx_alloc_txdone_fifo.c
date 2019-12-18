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
struct ath10k_htt {int /*<<< orphan*/  txdone_fifo; int /*<<< orphan*/  max_num_pending_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int kfifo_alloc (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 size_t roundup_pow_of_two (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_htt_tx_alloc_txdone_fifo(struct ath10k_htt *htt)
{
	int ret;
	size_t size;

	size = roundup_pow_of_two(htt->max_num_pending_tx);
	ret = kfifo_alloc(&htt->txdone_fifo, size, GFP_KERNEL);
	return ret;
}