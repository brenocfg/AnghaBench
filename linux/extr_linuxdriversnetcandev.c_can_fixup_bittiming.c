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
typedef  unsigned long u64 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int freq; } ;
struct can_priv {TYPE_1__ clock; } ;
struct can_bittiming_const {int sjw_max; int tseg1_min; int tseg1_max; int tseg2_min; int tseg2_max; int brp_inc; int brp_min; int brp_max; } ;
struct can_bittiming {int prop_seg; int phase_seg1; int sjw; int phase_seg2; int brp; int bitrate; int sample_point; scalar_t__ tq; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  do_div (unsigned long,unsigned long) ; 
 struct can_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int can_fixup_bittiming(struct net_device *dev, struct can_bittiming *bt,
			       const struct can_bittiming_const *btc)
{
	struct can_priv *priv = netdev_priv(dev);
	int tseg1, alltseg;
	u64 brp64;

	tseg1 = bt->prop_seg + bt->phase_seg1;
	if (!bt->sjw)
		bt->sjw = 1;
	if (bt->sjw > btc->sjw_max ||
	    tseg1 < btc->tseg1_min || tseg1 > btc->tseg1_max ||
	    bt->phase_seg2 < btc->tseg2_min || bt->phase_seg2 > btc->tseg2_max)
		return -ERANGE;

	brp64 = (u64)priv->clock.freq * (u64)bt->tq;
	if (btc->brp_inc > 1)
		do_div(brp64, btc->brp_inc);
	brp64 += 500000000UL - 1;
	do_div(brp64, 1000000000UL); /* the practicable BRP */
	if (btc->brp_inc > 1)
		brp64 *= btc->brp_inc;
	bt->brp = (u32)brp64;

	if (bt->brp < btc->brp_min || bt->brp > btc->brp_max)
		return -EINVAL;

	alltseg = bt->prop_seg + bt->phase_seg1 + bt->phase_seg2 + 1;
	bt->bitrate = priv->clock.freq / (bt->brp * alltseg);
	bt->sample_point = ((tseg1 + 1) * 1000) / alltseg;

	return 0;
}