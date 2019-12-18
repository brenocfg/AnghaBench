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
struct vid_vrfb_dma {int tx_status; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void omap_vout_vrfb_dma_tx_callback(void *data)
{
	struct vid_vrfb_dma *t = (struct vid_vrfb_dma *) data;

	t->tx_status = 1;
	wake_up_interruptible(&t->wait);
}