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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct rcar_canfd_channel {int channel; TYPE_1__ can; scalar_t__ base; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  RCANFD_CCTR (int) ; 
 int /*<<< orphan*/  RCANFD_CCTR_CHDMC_COPM ; 
 int /*<<< orphan*/  RCANFD_CCTR_CHMDC_MASK ; 
 int /*<<< orphan*/  RCANFD_CFCC (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCANFD_CFCC_CFE ; 
 int /*<<< orphan*/  RCANFD_CFFIFO_IDX ; 
 scalar_t__ RCANFD_CSTS (int) ; 
 int RCANFD_CSTS_COMSTS ; 
 int /*<<< orphan*/  RCANFD_RFCC (int) ; 
 int /*<<< orphan*/  RCANFD_RFCC_RFE ; 
 int RCANFD_RFFIFO_IDX ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct rcar_canfd_channel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcar_canfd_disable_channel_interrupts (struct rcar_canfd_channel*) ; 
 int /*<<< orphan*/  rcar_canfd_enable_channel_interrupts (struct rcar_canfd_channel*) ; 
 int /*<<< orphan*/  rcar_canfd_set_bit (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_canfd_set_bittiming (struct net_device*) ; 
 int /*<<< orphan*/  rcar_canfd_update_bit (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int) ; 

__attribute__((used)) static int rcar_canfd_start(struct net_device *ndev)
{
	struct rcar_canfd_channel *priv = netdev_priv(ndev);
	int err = -EOPNOTSUPP;
	u32 sts, ch = priv->channel;
	u32 ridx = ch + RCANFD_RFFIFO_IDX;

	rcar_canfd_set_bittiming(ndev);

	rcar_canfd_enable_channel_interrupts(priv);

	/* Set channel to Operational mode */
	rcar_canfd_update_bit(priv->base, RCANFD_CCTR(ch),
			      RCANFD_CCTR_CHMDC_MASK, RCANFD_CCTR_CHDMC_COPM);

	/* Verify channel mode change */
	err = readl_poll_timeout((priv->base + RCANFD_CSTS(ch)), sts,
				 (sts & RCANFD_CSTS_COMSTS), 2, 500000);
	if (err) {
		netdev_err(ndev, "channel %u communication state failed\n", ch);
		goto fail_mode_change;
	}

	/* Enable Common & Rx FIFO */
	rcar_canfd_set_bit(priv->base, RCANFD_CFCC(ch, RCANFD_CFFIFO_IDX),
			   RCANFD_CFCC_CFE);
	rcar_canfd_set_bit(priv->base, RCANFD_RFCC(ridx), RCANFD_RFCC_RFE);

	priv->can.state = CAN_STATE_ERROR_ACTIVE;
	return 0;

fail_mode_change:
	rcar_canfd_disable_channel_interrupts(priv);
	return err;
}