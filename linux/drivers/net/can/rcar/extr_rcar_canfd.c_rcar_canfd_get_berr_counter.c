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
typedef  int /*<<< orphan*/  u32 ;
struct rcar_canfd_channel {int /*<<< orphan*/  base; int /*<<< orphan*/  channel; } ;
struct net_device {int dummy; } ;
struct can_berr_counter {int /*<<< orphan*/  rxerr; int /*<<< orphan*/  txerr; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCANFD_CSTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCANFD_CSTS_RECCNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCANFD_CSTS_TECCNT (int /*<<< orphan*/ ) ; 
 struct rcar_canfd_channel* netdev_priv (struct net_device const*) ; 
 int /*<<< orphan*/  rcar_canfd_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcar_canfd_get_berr_counter(const struct net_device *dev,
				       struct can_berr_counter *bec)
{
	struct rcar_canfd_channel *priv = netdev_priv(dev);
	u32 val, ch = priv->channel;

	/* Peripheral clock is already enabled in probe */
	val = rcar_canfd_read(priv->base, RCANFD_CSTS(ch));
	bec->txerr = RCANFD_CSTS_TECCNT(val);
	bec->rxerr = RCANFD_CSTS_RECCNT(val);
	return 0;
}