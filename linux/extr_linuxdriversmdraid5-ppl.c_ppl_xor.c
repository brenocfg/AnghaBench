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
struct page {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
struct async_submit_ctl {int dummy; } ;

/* Variables and functions */
 int ASYNC_TX_ACK ; 
 int ASYNC_TX_XOR_DROP_DST ; 
 int /*<<< orphan*/  async_tx_quiesce (struct dma_async_tx_descriptor**) ; 
 struct dma_async_tx_descriptor* async_xor (struct page*,struct page**,int /*<<< orphan*/ ,int,int,struct async_submit_ctl*) ; 
 int /*<<< orphan*/  init_async_submit (struct async_submit_ctl*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ppl_xor(int size, struct page *page1, struct page *page2)
{
	struct async_submit_ctl submit;
	struct dma_async_tx_descriptor *tx;
	struct page *xor_srcs[] = { page1, page2 };

	init_async_submit(&submit, ASYNC_TX_ACK|ASYNC_TX_XOR_DROP_DST,
			  NULL, NULL, NULL, NULL);
	tx = async_xor(page1, xor_srcs, 0, 2, size, &submit);

	async_tx_quiesce(&tx);
}