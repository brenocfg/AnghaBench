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
typedef  int u32 ;
typedef  int u16 ;
struct rtl_coalesce_scale {int* nsecs; } ;
struct rtl8169_private {int cp_cmd; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int /*<<< orphan*/  tx_coalesce_usecs; int /*<<< orphan*/  tx_max_coalesced_frames; int /*<<< orphan*/  rx_coalesce_usecs; int /*<<< orphan*/  rx_max_coalesced_frames; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPlusCmd ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int INTT_MASK ; 
 scalar_t__ IS_ERR (struct rtl_coalesce_scale const*) ; 
 int /*<<< orphan*/  IntrMitigate ; 
 int PTR_ERR (struct rtl_coalesce_scale const*) ; 
 int RTL_COALESCE_FRAME_MAX ; 
 int RTL_COALESCE_SHIFT ; 
 int /*<<< orphan*/  RTL_R16 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W16 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int max (int,int) ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 struct rtl_coalesce_scale* rtl_coalesce_choose_scale (struct net_device*,int,int*) ; 
 scalar_t__ rtl_is_8125 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_lock_work (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_unlock_work (struct rtl8169_private*) ; 
 int swab16 (int) ; 

__attribute__((used)) static int rtl_set_coalesce(struct net_device *dev, struct ethtool_coalesce *ec)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	const struct rtl_coalesce_scale *scale;
	struct {
		u32 frames;
		u32 usecs;
	} coal_settings [] = {
		{ ec->rx_max_coalesced_frames, ec->rx_coalesce_usecs },
		{ ec->tx_max_coalesced_frames, ec->tx_coalesce_usecs }
	}, *p = coal_settings;
	u16 w = 0, cp01;
	int i;

	if (rtl_is_8125(tp))
		return -EOPNOTSUPP;

	scale = rtl_coalesce_choose_scale(dev,
			max(p[0].usecs, p[1].usecs) * 1000, &cp01);
	if (IS_ERR(scale))
		return PTR_ERR(scale);

	for (i = 0; i < 2; i++, p++) {
		u32 units;

		/*
		 * accept max_frames=1 we returned in rtl_get_coalesce.
		 * accept it not only when usecs=0 because of e.g. the following scenario:
		 *
		 * - both rx_usecs=0 & rx_frames=0 in hardware (no delay on RX)
		 * - rtl_get_coalesce returns rx_usecs=0, rx_frames=1
		 * - then user does `ethtool -C eth0 rx-usecs 100`
		 *
		 * since ethtool sends to kernel whole ethtool_coalesce
		 * settings, if we do not handle rx_usecs=!0, rx_frames=1
		 * we'll reject it below in `frames % 4 != 0`.
		 */
		if (p->frames == 1) {
			p->frames = 0;
		}

		units = p->usecs * 1000 / scale->nsecs[i];
		if (p->frames > RTL_COALESCE_FRAME_MAX || p->frames % 4)
			return -EINVAL;

		w <<= RTL_COALESCE_SHIFT;
		w |= units;
		w <<= RTL_COALESCE_SHIFT;
		w |= p->frames >> 2;
	}

	rtl_lock_work(tp);

	RTL_W16(tp, IntrMitigate, swab16(w));

	tp->cp_cmd = (tp->cp_cmd & ~INTT_MASK) | cp01;
	RTL_W16(tp, CPlusCmd, tp->cp_cmd);
	RTL_R16(tp, CPlusCmd);

	rtl_unlock_work(tp);

	return 0;
}