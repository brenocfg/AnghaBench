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
typedef  int /*<<< orphan*/  u32 ;
struct ptp_clock_info {scalar_t__ (* adjfreq ) (struct ptp_clock_info*,int /*<<< orphan*/ ) ;} ;
struct e1000_hw {int dummy; } ;
struct e1000_adapter {int flags; int /*<<< orphan*/  hwtstamp_config; int /*<<< orphan*/  systim_lock; int /*<<< orphan*/  cc; int /*<<< orphan*/  tc; TYPE_1__* pdev; int /*<<< orphan*/  ptp_delta; struct e1000_hw hw; struct ptp_clock_info ptp_clock_info; } ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FLAG_HAS_HW_TIMESTAMP ; 
 int /*<<< orphan*/  TIMINCA ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  e1000e_config_hwtstamp (struct e1000_adapter*,int /*<<< orphan*/ *) ; 
 scalar_t__ e1000e_get_base_timinca (struct e1000_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ stub1 (struct ptp_clock_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timecounter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000e_systim_reset(struct e1000_adapter *adapter)
{
	struct ptp_clock_info *info = &adapter->ptp_clock_info;
	struct e1000_hw *hw = &adapter->hw;
	unsigned long flags;
	u32 timinca;
	s32 ret_val;

	if (!(adapter->flags & FLAG_HAS_HW_TIMESTAMP))
		return;

	if (info->adjfreq) {
		/* restore the previous ptp frequency delta */
		ret_val = info->adjfreq(info, adapter->ptp_delta);
	} else {
		/* set the default base frequency if no adjustment possible */
		ret_val = e1000e_get_base_timinca(adapter, &timinca);
		if (!ret_val)
			ew32(TIMINCA, timinca);
	}

	if (ret_val) {
		dev_warn(&adapter->pdev->dev,
			 "Failed to restore TIMINCA clock rate delta: %d\n",
			 ret_val);
		return;
	}

	/* reset the systim ns time counter */
	spin_lock_irqsave(&adapter->systim_lock, flags);
	timecounter_init(&adapter->tc, &adapter->cc,
			 ktime_to_ns(ktime_get_real()));
	spin_unlock_irqrestore(&adapter->systim_lock, flags);

	/* restore the previous hwtstamp configuration settings */
	e1000e_config_hwtstamp(adapter, &adapter->hwtstamp_config);
}