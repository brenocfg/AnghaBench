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
struct be_queue_info {int dummy; } ;
struct be_tx_obj {struct be_queue_info q; } ;
struct be_eth_wrb {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  queue_head_inc (struct be_queue_info*) ; 
 struct be_eth_wrb* queue_head_node (struct be_queue_info*) ; 
 int /*<<< orphan*/  wrb_fill (struct be_eth_wrb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void be_tx_setup_wrb_frag(struct be_tx_obj *txo, dma_addr_t busaddr,
				 int len)
{
	struct be_eth_wrb *wrb;
	struct be_queue_info *txq = &txo->q;

	wrb = queue_head_node(txq);
	wrb_fill(wrb, busaddr, len);
	queue_head_inc(txq);
}