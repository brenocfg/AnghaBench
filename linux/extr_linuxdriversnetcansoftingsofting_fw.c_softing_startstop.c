#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  restarts; } ;
struct can_bittiming {int brp; int sjw; int phase_seg1; int prop_seg; int phase_seg2; } ;
struct TYPE_13__ {int ctrlmode; TYPE_5__ can_stats; int /*<<< orphan*/  state; struct can_bittiming bittiming; } ;
struct TYPE_8__ {scalar_t__ echo_get; scalar_t__ echo_put; scalar_t__ pending; } ;
struct softing_priv {int index; int output; TYPE_6__ can; TYPE_1__ tx; struct softing* card; } ;
struct TYPE_14__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  up; } ;
struct TYPE_9__ {scalar_t__ pending; } ;
struct softing {struct net_device** net; TYPE_7__ fw; int /*<<< orphan*/ * dpram; TYPE_4__* pdat; TYPE_3__* pdev; TYPE_2__ tx; } ;
struct net_device {int dummy; } ;
struct can_frame {int can_id; int /*<<< orphan*/  can_dlc; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_11__ {int generation; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct net_device**) ; 
 int CAN_CTRLMODE_3_SAMPLES ; 
 int /*<<< orphan*/  CAN_ERR_DLC ; 
 int CAN_ERR_FLAG ; 
 int CAN_ERR_RESTARTED ; 
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 int DPRAM_FCT_PARAM ; 
 size_t DPRAM_INFO_BUSSTATE ; 
 size_t DPRAM_INFO_BUSSTATE2 ; 
 size_t DPRAM_V2_IRQ_TOHOST ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  iowrite16 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct can_frame*,int /*<<< orphan*/ ,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct softing_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  open_candev (struct net_device*) ; 
 int softing_enable_irq (struct softing*,int) ; 
 scalar_t__ softing_error_reporting (struct net_device*) ; 
 int softing_fct_cmd (struct softing*,int,char*) ; 
 int /*<<< orphan*/  softing_initialize_timestamp (struct softing*) ; 
 int /*<<< orphan*/  softing_netdev_rx (struct net_device*,struct can_frame*,int /*<<< orphan*/ ) ; 
 int softing_reset_chip (struct softing*) ; 
 int /*<<< orphan*/  wmb () ; 

int softing_startstop(struct net_device *dev, int up)
{
	int ret;
	struct softing *card;
	struct softing_priv *priv;
	struct net_device *netdev;
	int bus_bitmask_start;
	int j, error_reporting;
	struct can_frame msg;
	const struct can_bittiming *bt;

	priv = netdev_priv(dev);
	card = priv->card;

	if (!card->fw.up)
		return -EIO;

	ret = mutex_lock_interruptible(&card->fw.lock);
	if (ret)
		return ret;

	bus_bitmask_start = 0;
	if (dev && up)
		/* prepare to start this bus as well */
		bus_bitmask_start |= (1 << priv->index);
	/* bring netdevs down */
	for (j = 0; j < ARRAY_SIZE(card->net); ++j) {
		netdev = card->net[j];
		if (!netdev)
			continue;
		priv = netdev_priv(netdev);

		if (dev != netdev)
			netif_stop_queue(netdev);

		if (netif_running(netdev)) {
			if (dev != netdev)
				bus_bitmask_start |= (1 << j);
			priv->tx.pending = 0;
			priv->tx.echo_put = 0;
			priv->tx.echo_get = 0;
			/*
			 * this bus' may just have called open_candev()
			 * which is rather stupid to call close_candev()
			 * already
			 * but we may come here from busoff recovery too
			 * in which case the echo_skb _needs_ flushing too.
			 * just be sure to call open_candev() again
			 */
			close_candev(netdev);
		}
		priv->can.state = CAN_STATE_STOPPED;
	}
	card->tx.pending = 0;

	softing_enable_irq(card, 0);
	ret = softing_reset_chip(card);
	if (ret)
		goto failed;
	if (!bus_bitmask_start)
		/* no busses to be brought up */
		goto card_done;

	if ((bus_bitmask_start & 1) && (bus_bitmask_start & 2)
			&& (softing_error_reporting(card->net[0])
				!= softing_error_reporting(card->net[1]))) {
		dev_alert(&card->pdev->dev,
				"err_reporting flag differs for busses\n");
		goto invalid;
	}
	error_reporting = 0;
	if (bus_bitmask_start & 1) {
		netdev = card->net[0];
		priv = netdev_priv(netdev);
		error_reporting += softing_error_reporting(netdev);
		/* init chip 1 */
		bt = &priv->can.bittiming;
		iowrite16(bt->brp, &card->dpram[DPRAM_FCT_PARAM + 2]);
		iowrite16(bt->sjw, &card->dpram[DPRAM_FCT_PARAM + 4]);
		iowrite16(bt->phase_seg1 + bt->prop_seg,
				&card->dpram[DPRAM_FCT_PARAM + 6]);
		iowrite16(bt->phase_seg2, &card->dpram[DPRAM_FCT_PARAM + 8]);
		iowrite16((priv->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES) ? 1 : 0,
				&card->dpram[DPRAM_FCT_PARAM + 10]);
		ret = softing_fct_cmd(card, 1, "initialize_chip[0]");
		if (ret < 0)
			goto failed;
		/* set mode */
		iowrite16(0, &card->dpram[DPRAM_FCT_PARAM + 2]);
		iowrite16(0, &card->dpram[DPRAM_FCT_PARAM + 4]);
		ret = softing_fct_cmd(card, 3, "set_mode[0]");
		if (ret < 0)
			goto failed;
		/* set filter */
		/* 11bit id & mask */
		iowrite16(0x0000, &card->dpram[DPRAM_FCT_PARAM + 2]);
		iowrite16(0x07ff, &card->dpram[DPRAM_FCT_PARAM + 4]);
		/* 29bit id.lo & mask.lo & id.hi & mask.hi */
		iowrite16(0x0000, &card->dpram[DPRAM_FCT_PARAM + 6]);
		iowrite16(0xffff, &card->dpram[DPRAM_FCT_PARAM + 8]);
		iowrite16(0x0000, &card->dpram[DPRAM_FCT_PARAM + 10]);
		iowrite16(0x1fff, &card->dpram[DPRAM_FCT_PARAM + 12]);
		ret = softing_fct_cmd(card, 7, "set_filter[0]");
		if (ret < 0)
			goto failed;
		/* set output control */
		iowrite16(priv->output, &card->dpram[DPRAM_FCT_PARAM + 2]);
		ret = softing_fct_cmd(card, 5, "set_output[0]");
		if (ret < 0)
			goto failed;
	}
	if (bus_bitmask_start & 2) {
		netdev = card->net[1];
		priv = netdev_priv(netdev);
		error_reporting += softing_error_reporting(netdev);
		/* init chip2 */
		bt = &priv->can.bittiming;
		iowrite16(bt->brp, &card->dpram[DPRAM_FCT_PARAM + 2]);
		iowrite16(bt->sjw, &card->dpram[DPRAM_FCT_PARAM + 4]);
		iowrite16(bt->phase_seg1 + bt->prop_seg,
				&card->dpram[DPRAM_FCT_PARAM + 6]);
		iowrite16(bt->phase_seg2, &card->dpram[DPRAM_FCT_PARAM + 8]);
		iowrite16((priv->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES) ? 1 : 0,
				&card->dpram[DPRAM_FCT_PARAM + 10]);
		ret = softing_fct_cmd(card, 2, "initialize_chip[1]");
		if (ret < 0)
			goto failed;
		/* set mode2 */
		iowrite16(0, &card->dpram[DPRAM_FCT_PARAM + 2]);
		iowrite16(0, &card->dpram[DPRAM_FCT_PARAM + 4]);
		ret = softing_fct_cmd(card, 4, "set_mode[1]");
		if (ret < 0)
			goto failed;
		/* set filter2 */
		/* 11bit id & mask */
		iowrite16(0x0000, &card->dpram[DPRAM_FCT_PARAM + 2]);
		iowrite16(0x07ff, &card->dpram[DPRAM_FCT_PARAM + 4]);
		/* 29bit id.lo & mask.lo & id.hi & mask.hi */
		iowrite16(0x0000, &card->dpram[DPRAM_FCT_PARAM + 6]);
		iowrite16(0xffff, &card->dpram[DPRAM_FCT_PARAM + 8]);
		iowrite16(0x0000, &card->dpram[DPRAM_FCT_PARAM + 10]);
		iowrite16(0x1fff, &card->dpram[DPRAM_FCT_PARAM + 12]);
		ret = softing_fct_cmd(card, 8, "set_filter[1]");
		if (ret < 0)
			goto failed;
		/* set output control2 */
		iowrite16(priv->output, &card->dpram[DPRAM_FCT_PARAM + 2]);
		ret = softing_fct_cmd(card, 6, "set_output[1]");
		if (ret < 0)
			goto failed;
	}
	/* enable_error_frame */
	/*
	 * Error reporting is switched off at the moment since
	 * the receiving of them is not yet 100% verified
	 * This should be enabled sooner or later
	 *
	if (error_reporting) {
		ret = softing_fct_cmd(card, 51, "enable_error_frame");
		if (ret < 0)
			goto failed;
	}
	*/
	/* initialize interface */
	iowrite16(1, &card->dpram[DPRAM_FCT_PARAM + 2]);
	iowrite16(1, &card->dpram[DPRAM_FCT_PARAM + 4]);
	iowrite16(1, &card->dpram[DPRAM_FCT_PARAM + 6]);
	iowrite16(1, &card->dpram[DPRAM_FCT_PARAM + 8]);
	iowrite16(1, &card->dpram[DPRAM_FCT_PARAM + 10]);
	iowrite16(1, &card->dpram[DPRAM_FCT_PARAM + 12]);
	iowrite16(1, &card->dpram[DPRAM_FCT_PARAM + 14]);
	iowrite16(1, &card->dpram[DPRAM_FCT_PARAM + 16]);
	iowrite16(1, &card->dpram[DPRAM_FCT_PARAM + 18]);
	iowrite16(1, &card->dpram[DPRAM_FCT_PARAM + 20]);
	ret = softing_fct_cmd(card, 17, "initialize_interface");
	if (ret < 0)
		goto failed;
	/* enable_fifo */
	ret = softing_fct_cmd(card, 36, "enable_fifo");
	if (ret < 0)
		goto failed;
	/* enable fifo tx ack */
	ret = softing_fct_cmd(card, 13, "fifo_tx_ack[0]");
	if (ret < 0)
		goto failed;
	/* enable fifo tx ack2 */
	ret = softing_fct_cmd(card, 14, "fifo_tx_ack[1]");
	if (ret < 0)
		goto failed;
	/* start_chip */
	ret = softing_fct_cmd(card, 11, "start_chip");
	if (ret < 0)
		goto failed;
	iowrite8(0, &card->dpram[DPRAM_INFO_BUSSTATE]);
	iowrite8(0, &card->dpram[DPRAM_INFO_BUSSTATE2]);
	if (card->pdat->generation < 2) {
		iowrite8(0, &card->dpram[DPRAM_V2_IRQ_TOHOST]);
		/* flush the DPRAM caches */
		wmb();
	}

	softing_initialize_timestamp(card);

	/*
	 * do socketcan notifications/status changes
	 * from here, no errors should occur, or the failed: part
	 * must be reviewed
	 */
	memset(&msg, 0, sizeof(msg));
	msg.can_id = CAN_ERR_FLAG | CAN_ERR_RESTARTED;
	msg.can_dlc = CAN_ERR_DLC;
	for (j = 0; j < ARRAY_SIZE(card->net); ++j) {
		if (!(bus_bitmask_start & (1 << j)))
			continue;
		netdev = card->net[j];
		if (!netdev)
			continue;
		priv = netdev_priv(netdev);
		priv->can.state = CAN_STATE_ERROR_ACTIVE;
		open_candev(netdev);
		if (dev != netdev) {
			/* notify other busses on the restart */
			softing_netdev_rx(netdev, &msg, 0);
			++priv->can.can_stats.restarts;
		}
		netif_wake_queue(netdev);
	}

	/* enable interrupts */
	ret = softing_enable_irq(card, 1);
	if (ret)
		goto failed;
card_done:
	mutex_unlock(&card->fw.lock);
	return 0;
invalid:
	ret = -EINVAL;
failed:
	softing_enable_irq(card, 0);
	softing_reset_chip(card);
	mutex_unlock(&card->fw.lock);
	/* bring all other interfaces down */
	for (j = 0; j < ARRAY_SIZE(card->net); ++j) {
		netdev = card->net[j];
		if (!netdev)
			continue;
		dev_close(netdev);
	}
	return ret;
}