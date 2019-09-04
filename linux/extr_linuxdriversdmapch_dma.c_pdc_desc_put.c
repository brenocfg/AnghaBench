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
struct pch_dma_desc {int /*<<< orphan*/  desc_node; int /*<<< orphan*/  tx_list; } ;
struct pch_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  free_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pdc_desc_put(struct pch_dma_chan *pd_chan,
			 struct pch_dma_desc *desc)
{
	if (desc) {
		spin_lock(&pd_chan->lock);
		list_splice_init(&desc->tx_list, &pd_chan->free_list);
		list_add(&desc->desc_node, &pd_chan->free_list);
		spin_unlock(&pd_chan->lock);
	}
}