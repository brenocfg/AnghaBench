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
struct can_bittiming {int phase_seg2; int phase_seg1; int prop_seg; int brp; int sjw; } ;
struct TYPE_2__ {int ctrlmode; struct can_bittiming bittiming; } ;
struct ti_hecc_priv {int /*<<< orphan*/  ndev; TYPE_1__ can; } ;

/* Variables and functions */
 int CAN_CTRLMODE_3_SAMPLES ; 
 int /*<<< orphan*/  HECC_CANBTC ; 
 int HECC_CANBTC_SAM ; 
 int /*<<< orphan*/  hecc_write (struct ti_hecc_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ti_hecc_set_btc(struct ti_hecc_priv *priv)
{
	struct can_bittiming *bit_timing = &priv->can.bittiming;
	u32 can_btc;

	can_btc = (bit_timing->phase_seg2 - 1) & 0x7;
	can_btc |= ((bit_timing->phase_seg1 + bit_timing->prop_seg - 1)
			& 0xF) << 3;
	if (priv->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES) {
		if (bit_timing->brp > 4)
			can_btc |= HECC_CANBTC_SAM;
		else
			netdev_warn(priv->ndev,
				    "WARN: Triple sampling not set due to h/w limitations");
	}
	can_btc |= ((bit_timing->sjw - 1) & 0x3) << 8;
	can_btc |= ((bit_timing->brp - 1) & 0xFF) << 16;

	/* ERM being set to 0 by default meaning resync at falling edge */

	hecc_write(priv, HECC_CANBTC, can_btc);
	netdev_info(priv->ndev, "setting CANBTC=%#x\n", can_btc);

	return 0;
}