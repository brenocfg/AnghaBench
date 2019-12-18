#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint ;
struct net_device {int dummy; } ;
struct fza_private {scalar_t__ state_chg_flag; int /*<<< orphan*/ ** rx_skbuff; scalar_t__* rx_dma; int /*<<< orphan*/  bdev; int /*<<< orphan*/  name; TYPE_1__* regs; int /*<<< orphan*/  state_chg_wait; int /*<<< orphan*/  lock; scalar_t__ state; int /*<<< orphan*/  reset_timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  control_a; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EIO ; 
 int /*<<< orphan*/  FZA_CONTROL_A_SHUT ; 
 int FZA_RING_RX_SIZE ; 
 int /*<<< orphan*/  FZA_RX_BUFFER_SIZE ; 
 scalar_t__ FZA_STATE_UNINITIALIZED ; 
 scalar_t__ FZA_STATUS_GET_STATE (int /*<<< orphan*/ ) ; 
 int HZ ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fza_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  readw_o (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 long wait_event_timeout (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  writew_o (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fza_close(struct net_device *dev)
{
	struct fza_private *fp = netdev_priv(dev);
	unsigned long flags;
	uint state;
	long t;
	int i;

	netif_stop_queue(dev);
	pr_debug("%s: queue stopped\n", fp->name);

	del_timer_sync(&fp->reset_timer);
	spin_lock_irqsave(&fp->lock, flags);
	fp->state = FZA_STATE_UNINITIALIZED;
	fp->state_chg_flag = 0;
	/* Shut the interface down. */
	writew_o(FZA_CONTROL_A_SHUT, &fp->regs->control_a);
	readw_o(&fp->regs->control_a);			/* Synchronize. */
	spin_unlock_irqrestore(&fp->lock, flags);

	/* DEC says SHUT needs up to 10 seconds to complete. */
	t = wait_event_timeout(fp->state_chg_wait, fp->state_chg_flag,
			       15 * HZ);
	state = FZA_STATUS_GET_STATE(readw_o(&fp->regs->status));
	if (fp->state_chg_flag == 0) {
		pr_err("%s: SHUT timed out!, state %x\n", fp->name, state);
		return -EIO;
	}
	if (state != FZA_STATE_UNINITIALIZED) {
		pr_err("%s: SHUT failed!, state %x\n", fp->name, state);
		return -EIO;
	}
	pr_debug("%s: SHUT: %lums elapsed\n", fp->name,
		 (15 * HZ - t) * 1000 / HZ);

	for (i = 0; i < FZA_RING_RX_SIZE; i++)
		if (fp->rx_skbuff[i]) {
			dma_unmap_single(fp->bdev, fp->rx_dma[i],
					 FZA_RX_BUFFER_SIZE, DMA_FROM_DEVICE);
			dev_kfree_skb(fp->rx_skbuff[i]);
			fp->rx_dma[i] = 0;
			fp->rx_skbuff[i] = NULL;
		}

	return 0;
}