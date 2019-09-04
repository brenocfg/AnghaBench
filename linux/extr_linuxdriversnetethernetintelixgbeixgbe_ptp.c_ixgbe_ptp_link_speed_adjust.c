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
struct ixgbe_adapter {int link_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_INCVAL_100 ; 
 int /*<<< orphan*/  IXGBE_INCVAL_10GB ; 
 int /*<<< orphan*/  IXGBE_INCVAL_1GB ; 
 int /*<<< orphan*/  IXGBE_INCVAL_SHIFT_100 ; 
 int /*<<< orphan*/  IXGBE_INCVAL_SHIFT_10GB ; 
 int /*<<< orphan*/  IXGBE_INCVAL_SHIFT_1GB ; 
#define  IXGBE_LINK_SPEED_100_FULL 130 
#define  IXGBE_LINK_SPEED_10GB_FULL 129 
#define  IXGBE_LINK_SPEED_1GB_FULL 128 

__attribute__((used)) static void ixgbe_ptp_link_speed_adjust(struct ixgbe_adapter *adapter,
					u32 *shift, u32 *incval)
{
	/**
	 * Scale the NIC cycle counter by a large factor so that
	 * relatively small corrections to the frequency can be added
	 * or subtracted. The drawbacks of a large factor include
	 * (a) the clock register overflows more quickly, (b) the cycle
	 * counter structure must be able to convert the systime value
	 * to nanoseconds using only a multiplier and a right-shift,
	 * and (c) the value must fit within the timinca register space
	 * => math based on internal DMA clock rate and available bits
	 *
	 * Note that when there is no link, internal DMA clock is same as when
	 * link speed is 10Gb. Set the registers correctly even when link is
	 * down to preserve the clock setting
	 */
	switch (adapter->link_speed) {
	case IXGBE_LINK_SPEED_100_FULL:
		*shift = IXGBE_INCVAL_SHIFT_100;
		*incval = IXGBE_INCVAL_100;
		break;
	case IXGBE_LINK_SPEED_1GB_FULL:
		*shift = IXGBE_INCVAL_SHIFT_1GB;
		*incval = IXGBE_INCVAL_1GB;
		break;
	case IXGBE_LINK_SPEED_10GB_FULL:
	default:
		*shift = IXGBE_INCVAL_SHIFT_10GB;
		*incval = IXGBE_INCVAL_10GB;
		break;
	}
}