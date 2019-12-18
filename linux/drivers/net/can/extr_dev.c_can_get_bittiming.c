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
struct net_device {int dummy; } ;
struct can_bittiming_const {int dummy; } ;
struct can_bittiming {scalar_t__ bitrate; scalar_t__ tq; } ;

/* Variables and functions */
 int EINVAL ; 
 int can_calc_bittiming (struct net_device*,struct can_bittiming*,struct can_bittiming_const const*) ; 
 int can_fixup_bittiming (struct net_device*,struct can_bittiming*,struct can_bittiming_const const*) ; 
 int can_validate_bitrate (struct net_device*,struct can_bittiming*,int /*<<< orphan*/  const*,unsigned int const) ; 

__attribute__((used)) static int can_get_bittiming(struct net_device *dev, struct can_bittiming *bt,
			     const struct can_bittiming_const *btc,
			     const u32 *bitrate_const,
			     const unsigned int bitrate_const_cnt)
{
	int err;

	/* Depending on the given can_bittiming parameter structure the CAN
	 * timing parameters are calculated based on the provided bitrate OR
	 * alternatively the CAN timing parameters (tq, prop_seg, etc.) are
	 * provided directly which are then checked and fixed up.
	 */
	if (!bt->tq && bt->bitrate && btc)
		err = can_calc_bittiming(dev, bt, btc);
	else if (bt->tq && !bt->bitrate && btc)
		err = can_fixup_bittiming(dev, bt, btc);
	else if (!bt->tq && bt->bitrate && bitrate_const)
		err = can_validate_bitrate(dev, bt, bitrate_const,
					   bitrate_const_cnt);
	else
		err = -EINVAL;

	return err;
}