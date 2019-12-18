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
struct sh_flctl {int /*<<< orphan*/ * chan_fifo0_tx; int /*<<< orphan*/ * chan_fifo0_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flctl_release_dma(struct sh_flctl *flctl)
{
	if (flctl->chan_fifo0_rx) {
		dma_release_channel(flctl->chan_fifo0_rx);
		flctl->chan_fifo0_rx = NULL;
	}
	if (flctl->chan_fifo0_tx) {
		dma_release_channel(flctl->chan_fifo0_tx);
		flctl->chan_fifo0_tx = NULL;
	}
}