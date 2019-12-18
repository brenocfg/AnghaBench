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
struct timespec64 {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct ixgbe_hw {int dummy; } ;
struct TYPE_2__ {int cycle_last; } ;
struct cyclecounter {int shift; int /*<<< orphan*/  mult; } ;
struct ixgbe_adapter {int flags2; int /*<<< orphan*/  tmreg_lock; TYPE_1__ hw_tc; struct ixgbe_hw hw; struct cyclecounter hw_cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ESDP ; 
 int IXGBE_ESDP_SDP0_DIR ; 
 int IXGBE_ESDP_SDP0_NATIVE ; 
 int IXGBE_FLAG2_PTP_PPS_ENABLED ; 
 int /*<<< orphan*/  IXGBE_FREQOUT0 ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_TRGTTIMH0 ; 
 int /*<<< orphan*/  IXGBE_TRGTTIML0 ; 
 int /*<<< orphan*/  IXGBE_TSAUXC ; 
 int IXGBE_TSAUXC_DIS_TS_CLEAR ; 
 int IXGBE_TSAUXC_EN_CLK ; 
 int IXGBE_TSAUXC_EN_TT0 ; 
 int IXGBE_TSAUXC_SDP0_INT ; 
 int IXGBE_TSAUXC_ST0 ; 
 int /*<<< orphan*/  IXGBE_TSSDP ; 
 int IXGBE_TSSDP_TS_SDP0_CLK0 ; 
 int IXGBE_TSSDP_TS_SDP0_EN ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int NS_PER_HALF_SEC ; 
 int NS_PER_SEC ; 
 int div_u64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div_u64_rem (int,int,int*) ; 
 struct timespec64 ns_to_timespec64 (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int timecounter_read (TYPE_1__*) ; 

__attribute__((used)) static void ixgbe_ptp_setup_sdp_X550(struct ixgbe_adapter *adapter)
{
	u32 esdp, tsauxc, freqout, trgttiml, trgttimh, rem, tssdp;
	struct cyclecounter *cc = &adapter->hw_cc;
	struct ixgbe_hw *hw = &adapter->hw;
	u64 ns = 0, clock_edge = 0;
	struct timespec64 ts;
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

	/* enable the Clock Out feature on SDP0, and use Target Time 0 to
	 * enable generation of interrupts on the clock change.
	 */
#define IXGBE_TSAUXC_DIS_TS_CLEAR 0x40000000
	tsauxc = (IXGBE_TSAUXC_EN_CLK | IXGBE_TSAUXC_ST0 |
		  IXGBE_TSAUXC_EN_TT0 | IXGBE_TSAUXC_SDP0_INT |
		  IXGBE_TSAUXC_DIS_TS_CLEAR);

	tssdp = (IXGBE_TSSDP_TS_SDP0_EN |
		 IXGBE_TSSDP_TS_SDP0_CLK0);

	/* Determine the clock time period to use. This assumes that the
	 * cycle counter shift is small enough to avoid overflowing a 32bit
	 * value.
	 */
	freqout = div_u64(NS_PER_HALF_SEC << cc->shift,  cc->mult);

	/* Read the current clock time, and save the cycle counter value */
	spin_lock_irqsave(&adapter->tmreg_lock, flags);
	ns = timecounter_read(&adapter->hw_tc);
	clock_edge = adapter->hw_tc.cycle_last;
	spin_unlock_irqrestore(&adapter->tmreg_lock, flags);

	/* Figure out how far past the next second we are */
	div_u64_rem(ns, NS_PER_SEC, &rem);

	/* Figure out how many nanoseconds to add to round the clock edge up
	 * to the next full second
	 */
	rem = (NS_PER_SEC - rem);

	/* Adjust the clock edge to align with the next full second. */
	clock_edge += div_u64(((u64)rem << cc->shift), cc->mult);

	/* X550 hardware stores the time in 32bits of 'billions of cycles' and
	 * 32bits of 'cycles'. There's no guarantee that cycles represents
	 * nanoseconds. However, we can use the math from a timespec64 to
	 * convert into the hardware representation.
	 *
	 * See ixgbe_ptp_read_X550() for more details.
	 */
	ts = ns_to_timespec64(clock_edge);
	trgttiml = (u32)ts.tv_nsec;
	trgttimh = (u32)ts.tv_sec;

	IXGBE_WRITE_REG(hw, IXGBE_FREQOUT0, freqout);
	IXGBE_WRITE_REG(hw, IXGBE_TRGTTIML0, trgttiml);
	IXGBE_WRITE_REG(hw, IXGBE_TRGTTIMH0, trgttimh);

	IXGBE_WRITE_REG(hw, IXGBE_ESDP, esdp);
	IXGBE_WRITE_REG(hw, IXGBE_TSSDP, tssdp);
	IXGBE_WRITE_REG(hw, IXGBE_TSAUXC, tsauxc);

	IXGBE_WRITE_FLUSH(hw);
}