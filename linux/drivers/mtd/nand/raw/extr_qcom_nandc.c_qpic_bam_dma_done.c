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
struct bam_transaction {int wait_second_completion; int /*<<< orphan*/  txn_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qpic_bam_dma_done(void *data)
{
	struct bam_transaction *bam_txn = data;

	/*
	 * In case of data transfer with NAND, 2 callbacks will be generated.
	 * One for command channel and another one for data channel.
	 * If current transaction has data descriptors
	 * (i.e. wait_second_completion is true), then set this to false
	 * and wait for second DMA descriptor completion.
	 */
	if (bam_txn->wait_second_completion)
		bam_txn->wait_second_completion = false;
	else
		complete(&bam_txn->txn_done);
}