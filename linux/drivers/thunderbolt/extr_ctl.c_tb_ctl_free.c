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
struct tb_ctl {int /*<<< orphan*/  frame_pool; int /*<<< orphan*/ * rx_packets; scalar_t__ tx; scalar_t__ rx; } ;

/* Variables and functions */
 int TB_CTL_RX_PKG_COUNT ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tb_ctl*) ; 
 int /*<<< orphan*/  tb_ctl_pkg_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_ring_free (scalar_t__) ; 

void tb_ctl_free(struct tb_ctl *ctl)
{
	int i;

	if (!ctl)
		return;

	if (ctl->rx)
		tb_ring_free(ctl->rx);
	if (ctl->tx)
		tb_ring_free(ctl->tx);

	/* free RX packets */
	for (i = 0; i < TB_CTL_RX_PKG_COUNT; i++)
		tb_ctl_pkg_free(ctl->rx_packets[i]);


	dma_pool_destroy(ctl->frame_pool);
	kfree(ctl);
}