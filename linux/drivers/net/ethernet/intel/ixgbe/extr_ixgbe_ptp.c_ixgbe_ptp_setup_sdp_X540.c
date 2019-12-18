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
typedef  int u64 ;
typedef  int u32 ;
struct ixgbe_hw {int dummy; } ;
struct TYPE_2__ {int cycle_last; } ;
struct cyclecounter {int shift; int /*<<< orphan*/  mult; } ;
struct ixgbe_adapter {int flags2; int /*<<< orphan*/  tmreg_lock; TYPE_1__ hw_tc; struct ixgbe_hw hw; struct cyclecounter hw_cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_CLKTIMH ; 
 int /*<<< orphan*/  IXGBE_CLKTIML ; 
 int /*<<< orphan*/  IXGBE_ESDP ; 
 int IXGBE_ESDP_SDP0_DIR ; 
 int IXGBE_ESDP_SDP0_NATIVE ; 
 int IXGBE_FLAG2_PTP_PPS_ENABLED ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_TRGTTIMH0 ; 
 int /*<<< orphan*/  IXGBE_TRGTTIML0 ; 
 int /*<<< orphan*/  IXGBE_TSAUXC ; 
 int IXGBE_TSAUXC_EN_CLK ; 
 int IXGBE_TSAUXC_SDP0_INT ; 
 int IXGBE_TSAUXC_SYNCLK ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int NS_PER_HALF_SEC ; 
 int NS_PER_SEC ; 
 int div_u64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div_u64_rem (int,int,int*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int timecounter_read (TYPE_1__*) ; 

__attribute__((used)) static void ixgbe_ptp_setup_sdp_X540(struct ixgbe_adapter *adapter)
{
	struct cyclecounter *cc = &adapter->hw_cc;
	struct ixgbe_hw *hw = &adapter->hw;
	u32 esdp, tsauxc, clktiml, clktimh, trgttiml, trgttimh, rem;
	u64 ns = 0, clock_edge = 0, clock_period;
	unsigned long flags;

	/* disable the pin first */
	IXGBE_WRITE_REG(hw, IXGBE_TSAUXC, 0x0);
	IXGBE_WRITE_FLUSH(hw);

	if (!(adapter->flags2 & IXGBE_FLAG2_PTP_PPS_ENABLED))
		return;

	esdp = IXGBE_READ_REG(hw, IXGBE_ESDP);

	/* enable the SDP0 pin as output, and connected to the
	 * native function for Timesync (ClockOut)
	 */
	esdp |= IXGBE_ESDP_SDP0_DIR |
		IXGBE_ESDP_SDP0_NATIVE;

	/* enable the Clock Out feature on SDP0, and allow
	 * interrupts to occur when the pin changes
	 */
	tsauxc = (IXGBE_TSAUXC_EN_CLK |
		  IXGBE_TSAUXC_SYNCLK |
		  IXGBE_TSAUXC_SDP0_INT);

	/* Determine the clock time period to use. This assumes that the
	 * cycle counter shift is small enough to avoid overflow.
	 */
	clock_period = div_u64((NS_PER_HALF_SEC << cc->shift), cc->mult);
	clktiml = (u32)(clock_period);
	clktimh = (u32)(clock_period >> 32);

	/* Read the current clock time, and save the cycle counter value */
	spin_lock_irqsave(&adapter->tmreg_lock, flags);
	ns = timecounter_read(&adapter->hw_tc);
	clock_edge = adapter->hw_tc.cycle_last;
	spin_unlock_irqrestore(&adapter->tmreg_lock, flags);

	/* Figure out how many seconds to add in order to round up */
	div_u64_rem(ns, NS_PER_SEC, &rem);

	/* Figure out how many nanoseconds to add to round the clock edge up
	 * to the next full second
	 */
	rem = (NS_PER_SEC - rem);

	/* Adjust the clock edge to align with the next full second. */
	clock_edge += div_u64(((u64)rem << cc->shift), cc->mult);
	trgttiml = (u32)clock_edge;
	trgttimh = (u32)(clock_edge >> 32);

	IXGBE_WRITE_REG(hw, IXGBE_CLKTIML, clktiml);
	IXGBE_WRITE_REG(hw, IXGBE_CLKTIMH, clktimh);
	IXGBE_WRITE_REG(hw, IXGBE_TRGTTIML0, trgttiml);
	IXGBE_WRITE_REG(hw, IXGBE_TRGTTIMH0, trgttimh);

	IXGBE_WRITE_REG(hw, IXGBE_ESDP, esdp);
	IXGBE_WRITE_REG(hw, IXGBE_TSAUXC, tsauxc);

	IXGBE_WRITE_FLUSH(hw);
}