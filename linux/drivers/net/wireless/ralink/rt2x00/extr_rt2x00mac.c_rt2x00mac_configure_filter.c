#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct rt2x00_dev {unsigned int packet_filter; TYPE_2__* ops; } ;
struct ieee80211_hw {struct rt2x00_dev* priv; } ;
struct TYPE_4__ {TYPE_1__* lib; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* config_filter ) (struct rt2x00_dev*,unsigned int) ;} ;

/* Variables and functions */
 unsigned int FIF_ALLMULTI ; 
 unsigned int FIF_CONTROL ; 
 unsigned int FIF_FCSFAIL ; 
 unsigned int FIF_OTHER_BSS ; 
 unsigned int FIF_PLCPFAIL ; 
 unsigned int FIF_PSPOLL ; 
 int /*<<< orphan*/  rt2x00_has_cap_control_filter_pspoll (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_has_cap_control_filters (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  stub1 (struct rt2x00_dev*,unsigned int) ; 

void rt2x00mac_configure_filter(struct ieee80211_hw *hw,
				unsigned int changed_flags,
				unsigned int *total_flags,
				u64 multicast)
{
	struct rt2x00_dev *rt2x00dev = hw->priv;

	/*
	 * Mask off any flags we are going to ignore
	 * from the total_flags field.
	 */
	*total_flags &=
	    FIF_ALLMULTI |
	    FIF_FCSFAIL |
	    FIF_PLCPFAIL |
	    FIF_CONTROL |
	    FIF_PSPOLL |
	    FIF_OTHER_BSS;

	/*
	 * Apply some rules to the filters:
	 * - Some filters imply different filters to be set.
	 * - Some things we can't filter out at all.
	 * - Multicast filter seems to kill broadcast traffic so never use it.
	 */
	*total_flags |= FIF_ALLMULTI;

	/*
	 * If the device has a single filter for all control frames,
	 * FIF_CONTROL and FIF_PSPOLL flags imply each other.
	 * And if the device has more than one filter for control frames
	 * of different types, but has no a separate filter for PS Poll frames,
	 * FIF_CONTROL flag implies FIF_PSPOLL.
	 */
	if (!rt2x00_has_cap_control_filters(rt2x00dev)) {
		if (*total_flags & FIF_CONTROL || *total_flags & FIF_PSPOLL)
			*total_flags |= FIF_CONTROL | FIF_PSPOLL;
	}
	if (!rt2x00_has_cap_control_filter_pspoll(rt2x00dev)) {
		if (*total_flags & FIF_CONTROL)
			*total_flags |= FIF_PSPOLL;
	}

	rt2x00dev->packet_filter = *total_flags;

	rt2x00dev->ops->lib->config_filter(rt2x00dev, *total_flags);
}