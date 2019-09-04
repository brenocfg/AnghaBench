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
struct TYPE_2__ {int type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_adapter {int /*<<< orphan*/  tmreg_lock; int /*<<< orphan*/  hw_cc; int /*<<< orphan*/  base_incval; struct ixgbe_hw hw; } ;
struct cyclecounter {int mult; int shift; void* read; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLOCKSOURCE_MASK (int) ; 
 int /*<<< orphan*/  IXGBE_EIMS ; 
 int IXGBE_EIMS_TIMESYNC ; 
 int IXGBE_FUSES0_300MHZ ; 
 int /*<<< orphan*/  IXGBE_FUSES0_GROUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_INCPER_SHIFT_82599 ; 
 int IXGBE_INCVAL_SHIFT_82599 ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SYSTIMH ; 
 int /*<<< orphan*/  IXGBE_SYSTIML ; 
 int /*<<< orphan*/  IXGBE_SYSTIMR ; 
 int /*<<< orphan*/  IXGBE_TIMINCA ; 
 int /*<<< orphan*/  IXGBE_TSAUXC ; 
 int IXGBE_TSAUXC_DISABLE_SYSTIME ; 
 int /*<<< orphan*/  IXGBE_TSIM ; 
 int IXGBE_TSIM_TXTS ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
#define  ixgbe_mac_82599EB 132 
#define  ixgbe_mac_X540 131 
#define  ixgbe_mac_X550 130 
#define  ixgbe_mac_X550EM_x 129 
#define  ixgbe_mac_x550em_a 128 
 int /*<<< orphan*/  ixgbe_ptp_link_speed_adjust (struct ixgbe_adapter*,int*,int*) ; 
 void* ixgbe_ptp_read_82599 ; 
 void* ixgbe_ptp_read_X550 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct cyclecounter*,int) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ixgbe_ptp_start_cyclecounter(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	struct cyclecounter cc;
	unsigned long flags;
	u32 incval = 0;
	u32 tsauxc = 0;
	u32 fuse0 = 0;

	/* For some of the boards below this mask is technically incorrect.
	 * The timestamp mask overflows at approximately 61bits. However the
	 * particular hardware does not overflow on an even bitmask value.
	 * Instead, it overflows due to conversion of upper 32bits billions of
	 * cycles. Timecounters are not really intended for this purpose so
	 * they do not properly function if the overflow point isn't 2^N-1.
	 * However, the actual SYSTIME values in question take ~138 years to
	 * overflow. In practice this means they won't actually overflow. A
	 * proper fix to this problem would require modification of the
	 * timecounter delta calculations.
	 */
	cc.mask = CLOCKSOURCE_MASK(64);
	cc.mult = 1;
	cc.shift = 0;

	switch (hw->mac.type) {
	case ixgbe_mac_X550EM_x:
		/* SYSTIME assumes X550EM_x board frequency is 300Mhz, and is
		 * designed to represent seconds and nanoseconds when this is
		 * the case. However, some revisions of hardware have a 400Mhz
		 * clock and we have to compensate for this frequency
		 * variation using corrected mult and shift values.
		 */
		fuse0 = IXGBE_READ_REG(hw, IXGBE_FUSES0_GROUP(0));
		if (!(fuse0 & IXGBE_FUSES0_300MHZ)) {
			cc.mult = 3;
			cc.shift = 2;
		}
		/* fallthrough */
	case ixgbe_mac_x550em_a:
	case ixgbe_mac_X550:
		cc.read = ixgbe_ptp_read_X550;

		/* enable SYSTIME counter */
		IXGBE_WRITE_REG(hw, IXGBE_SYSTIMR, 0);
		IXGBE_WRITE_REG(hw, IXGBE_SYSTIML, 0);
		IXGBE_WRITE_REG(hw, IXGBE_SYSTIMH, 0);
		tsauxc = IXGBE_READ_REG(hw, IXGBE_TSAUXC);
		IXGBE_WRITE_REG(hw, IXGBE_TSAUXC,
				tsauxc & ~IXGBE_TSAUXC_DISABLE_SYSTIME);
		IXGBE_WRITE_REG(hw, IXGBE_TSIM, IXGBE_TSIM_TXTS);
		IXGBE_WRITE_REG(hw, IXGBE_EIMS, IXGBE_EIMS_TIMESYNC);

		IXGBE_WRITE_FLUSH(hw);
		break;
	case ixgbe_mac_X540:
		cc.read = ixgbe_ptp_read_82599;

		ixgbe_ptp_link_speed_adjust(adapter, &cc.shift, &incval);
		IXGBE_WRITE_REG(hw, IXGBE_TIMINCA, incval);
		break;
	case ixgbe_mac_82599EB:
		cc.read = ixgbe_ptp_read_82599;

		ixgbe_ptp_link_speed_adjust(adapter, &cc.shift, &incval);
		incval >>= IXGBE_INCVAL_SHIFT_82599;
		cc.shift -= IXGBE_INCVAL_SHIFT_82599;
		IXGBE_WRITE_REG(hw, IXGBE_TIMINCA,
				BIT(IXGBE_INCPER_SHIFT_82599) | incval);
		break;
	default:
		/* other devices aren't supported */
		return;
	}

	/* update the base incval used to calculate frequency adjustment */
	WRITE_ONCE(adapter->base_incval, incval);
	smp_mb();

	/* need lock to prevent incorrect read while modifying cyclecounter */
	spin_lock_irqsave(&adapter->tmreg_lock, flags);
	memcpy(&adapter->hw_cc, &cc, sizeof(adapter->hw_cc));
	spin_unlock_irqrestore(&adapter->tmreg_lock, flags);
}