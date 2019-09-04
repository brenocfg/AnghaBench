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
struct TYPE_2__ {int shift; } ;
struct ixgbe_adapter {int flags2; int /*<<< orphan*/  hw_tc; TYPE_1__ hw_cc; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_CLKTIMH ; 
 int /*<<< orphan*/  IXGBE_CLKTIML ; 
 int /*<<< orphan*/  IXGBE_ESDP ; 
 int IXGBE_ESDP_SDP0_DIR ; 
 int IXGBE_ESDP_SDP0_NATIVE ; 
 int IXGBE_FLAG2_PTP_PPS_ENABLED ; 
 int IXGBE_PTP_PPS_HALF_SECOND ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SYSTIMH ; 
 int /*<<< orphan*/  IXGBE_SYSTIML ; 
 int /*<<< orphan*/  IXGBE_TRGTTIMH0 ; 
 int /*<<< orphan*/  IXGBE_TRGTTIML0 ; 
 int /*<<< orphan*/  IXGBE_TSAUXC ; 
 int IXGBE_TSAUXC_EN_CLK ; 
 int IXGBE_TSAUXC_SDP0_INT ; 
 int IXGBE_TSAUXC_SYNCLK ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  div_u64_rem (int,int,int*) ; 
 int timecounter_cyc2time (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ixgbe_ptp_setup_sdp_x540(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	int shift = adapter->hw_cc.shift;
	u32 esdp, tsauxc, clktiml, clktimh, trgttiml, trgttimh, rem;
	u64 ns = 0, clock_edge = 0;

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
	tsauxc = IXGBE_TSAUXC_EN_CLK |
		 IXGBE_TSAUXC_SYNCLK |
		 IXGBE_TSAUXC_SDP0_INT;

	/* clock period (or pulse length) */
	clktiml = (u32)(IXGBE_PTP_PPS_HALF_SECOND << shift);
	clktimh = (u32)((IXGBE_PTP_PPS_HALF_SECOND << shift) >> 32);

	/* Account for the cyclecounter wrap-around value by
	 * using the converted ns value of the current time to
	 * check for when the next aligned second would occur.
	 */
	clock_edge |= (u64)IXGBE_READ_REG(hw, IXGBE_SYSTIML);
	clock_edge |= (u64)IXGBE_READ_REG(hw, IXGBE_SYSTIMH) << 32;
	ns = timecounter_cyc2time(&adapter->hw_tc, clock_edge);

	div_u64_rem(ns, IXGBE_PTP_PPS_HALF_SECOND, &rem);
	clock_edge += ((IXGBE_PTP_PPS_HALF_SECOND - (u64)rem) << shift);

	/* specify the initial clock start time */
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