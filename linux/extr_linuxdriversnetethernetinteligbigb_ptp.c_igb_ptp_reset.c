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
struct timespec64 {int dummy; } ;
struct TYPE_2__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {int ptp_flags; int /*<<< orphan*/  ptp_overflow_work; int /*<<< orphan*/  tmreg_lock; int /*<<< orphan*/  cc; int /*<<< orphan*/  tc; int /*<<< orphan*/  pps_sys_wrap_on; struct e1000_hw hw; int /*<<< orphan*/  tstamp_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_IMS ; 
 int E1000_IMS_TS ; 
 int /*<<< orphan*/  E1000_TIMINCA ; 
 int /*<<< orphan*/  E1000_TSAUXC ; 
 int /*<<< orphan*/  E1000_TSIM ; 
 int /*<<< orphan*/  E1000_TSSDP ; 
 int IGB_PTP_OVERFLOW_CHECK ; 
 int /*<<< orphan*/  IGB_SYSTIM_OVERFLOW_PERIOD ; 
 int INCPERIOD_82576 ; 
 int INCVALUE_82576 ; 
 int TSINTR_SYS_WRAP ; 
 int TSYNC_INTERRUPTS ; 
#define  e1000_82576 133 
#define  e1000_82580 132 
#define  e1000_i210 131 
#define  e1000_i211 130 
#define  e1000_i350 129 
#define  e1000_i354 128 
 int /*<<< orphan*/  igb_ptp_set_timestamp_mode (struct igb_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igb_ptp_write_i210 (struct igb_adapter*,struct timespec64*) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 struct timespec64 ktime_to_timespec64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timecounter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrfl () ; 

void igb_ptp_reset(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	unsigned long flags;

	/* reset the tstamp_config */
	igb_ptp_set_timestamp_mode(adapter, &adapter->tstamp_config);

	spin_lock_irqsave(&adapter->tmreg_lock, flags);

	switch (adapter->hw.mac.type) {
	case e1000_82576:
		/* Dial the nominal frequency. */
		wr32(E1000_TIMINCA, INCPERIOD_82576 | INCVALUE_82576);
		break;
	case e1000_82580:
	case e1000_i354:
	case e1000_i350:
	case e1000_i210:
	case e1000_i211:
		wr32(E1000_TSAUXC, 0x0);
		wr32(E1000_TSSDP, 0x0);
		wr32(E1000_TSIM,
		     TSYNC_INTERRUPTS |
		     (adapter->pps_sys_wrap_on ? TSINTR_SYS_WRAP : 0));
		wr32(E1000_IMS, E1000_IMS_TS);
		break;
	default:
		/* No work to do. */
		goto out;
	}

	/* Re-initialize the timer. */
	if ((hw->mac.type == e1000_i210) || (hw->mac.type == e1000_i211)) {
		struct timespec64 ts = ktime_to_timespec64(ktime_get_real());

		igb_ptp_write_i210(adapter, &ts);
	} else {
		timecounter_init(&adapter->tc, &adapter->cc,
				 ktime_to_ns(ktime_get_real()));
	}
out:
	spin_unlock_irqrestore(&adapter->tmreg_lock, flags);

	wrfl();

	if (adapter->ptp_flags & IGB_PTP_OVERFLOW_CHECK)
		schedule_delayed_work(&adapter->ptp_overflow_work,
				      IGB_SYSTIM_OVERFLOW_PERIOD);
}