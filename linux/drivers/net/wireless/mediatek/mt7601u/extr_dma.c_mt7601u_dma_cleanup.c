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
struct mt7601u_dev {int /*<<< orphan*/  tx_tasklet; int /*<<< orphan*/  rx_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt7601u_free_rx (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mt7601u_free_tx (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mt7601u_kill_rx (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void mt7601u_dma_cleanup(struct mt7601u_dev *dev)
{
	mt7601u_kill_rx(dev);

	tasklet_kill(&dev->rx_tasklet);

	mt7601u_free_rx(dev);
	mt7601u_free_tx(dev);

	tasklet_kill(&dev->tx_tasklet);
}