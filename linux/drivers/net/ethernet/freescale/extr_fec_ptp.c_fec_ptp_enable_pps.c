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
typedef  scalar_t__ uint ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct timespec64 {scalar_t__ tv_nsec; } ;
struct TYPE_4__ {int mask; } ;
struct fec_enet_private {scalar_t__ pps_enable; int reload_period; int next_counter; int /*<<< orphan*/  tmreg_lock; int /*<<< orphan*/  pps_channel; scalar_t__ hwp; TYPE_2__ cc; int /*<<< orphan*/  tc; TYPE_1__* pdev; scalar_t__ hwts_rx_en; scalar_t__ hwts_tx_en; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_PPS_CHANNEL ; 
 int EINVAL ; 
 scalar_t__ FEC_ATIME ; 
 scalar_t__ FEC_ATIME_CTRL ; 
 int FEC_HIGH_PULSE ; 
 scalar_t__ FEC_TCCR (int /*<<< orphan*/ ) ; 
 scalar_t__ FEC_TCSR (int /*<<< orphan*/ ) ; 
 int FEC_T_CTRL_CAPTURE ; 
 int FEC_T_CTRL_PINPER ; 
 int FEC_T_TDRE_OFFSET ; 
 int FEC_T_TF_MASK ; 
 int FEC_T_TF_OFFSET ; 
 int FEC_T_TIE_OFFSET ; 
 int FEC_T_TMODE_MASK ; 
 int FEC_T_TMODE_OFFSET ; 
 int NSEC_PER_SEC ; 
 int PPS_OUPUT_RELOAD_PERIOD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct timespec64 ns_to_timespec64 (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timecounter_cyc2time (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  timecounter_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int fec_ptp_enable_pps(struct fec_enet_private *fep, uint enable)
{
	unsigned long flags;
	u32 val, tempval;
	struct timespec64 ts;
	u64 ns;
	val = 0;

	if (!(fep->hwts_tx_en || fep->hwts_rx_en)) {
		dev_err(&fep->pdev->dev, "No ptp stack is running\n");
		return -EINVAL;
	}

	if (fep->pps_enable == enable)
		return 0;

	fep->pps_channel = DEFAULT_PPS_CHANNEL;
	fep->reload_period = PPS_OUPUT_RELOAD_PERIOD;

	spin_lock_irqsave(&fep->tmreg_lock, flags);

	if (enable) {
		/* clear capture or output compare interrupt status if have.
		 */
		writel(FEC_T_TF_MASK, fep->hwp + FEC_TCSR(fep->pps_channel));

		/* It is recommended to double check the TMODE field in the
		 * TCSR register to be cleared before the first compare counter
		 * is written into TCCR register. Just add a double check.
		 */
		val = readl(fep->hwp + FEC_TCSR(fep->pps_channel));
		do {
			val &= ~(FEC_T_TMODE_MASK);
			writel(val, fep->hwp + FEC_TCSR(fep->pps_channel));
			val = readl(fep->hwp + FEC_TCSR(fep->pps_channel));
		} while (val & FEC_T_TMODE_MASK);

		/* Dummy read counter to update the counter */
		timecounter_read(&fep->tc);
		/* We want to find the first compare event in the next
		 * second point. So we need to know what the ptp time
		 * is now and how many nanoseconds is ahead to get next second.
		 * The remaining nanosecond ahead before the next second would be
		 * NSEC_PER_SEC - ts.tv_nsec. Add the remaining nanoseconds
		 * to current timer would be next second.
		 */
		tempval = readl(fep->hwp + FEC_ATIME_CTRL);
		tempval |= FEC_T_CTRL_CAPTURE;
		writel(tempval, fep->hwp + FEC_ATIME_CTRL);

		tempval = readl(fep->hwp + FEC_ATIME);
		/* Convert the ptp local counter to 1588 timestamp */
		ns = timecounter_cyc2time(&fep->tc, tempval);
		ts = ns_to_timespec64(ns);

		/* The tempval is  less than 3 seconds, and  so val is less than
		 * 4 seconds. No overflow for 32bit calculation.
		 */
		val = NSEC_PER_SEC - (u32)ts.tv_nsec + tempval;

		/* Need to consider the situation that the current time is
		 * very close to the second point, which means NSEC_PER_SEC
		 * - ts.tv_nsec is close to be zero(For example 20ns); Since the timer
		 * is still running when we calculate the first compare event, it is
		 * possible that the remaining nanoseonds run out before the compare
		 * counter is calculated and written into TCCR register. To avoid
		 * this possibility, we will set the compare event to be the next
		 * of next second. The current setting is 31-bit timer and wrap
		 * around over 2 seconds. So it is okay to set the next of next
		 * seond for the timer.
		 */
		val += NSEC_PER_SEC;

		/* We add (2 * NSEC_PER_SEC - (u32)ts.tv_nsec) to current
		 * ptp counter, which maybe cause 32-bit wrap. Since the
		 * (NSEC_PER_SEC - (u32)ts.tv_nsec) is less than 2 second.
		 * We can ensure the wrap will not cause issue. If the offset
		 * is bigger than fep->cc.mask would be a error.
		 */
		val &= fep->cc.mask;
		writel(val, fep->hwp + FEC_TCCR(fep->pps_channel));

		/* Calculate the second the compare event timestamp */
		fep->next_counter = (val + fep->reload_period) & fep->cc.mask;

		/* * Enable compare event when overflow */
		val = readl(fep->hwp + FEC_ATIME_CTRL);
		val |= FEC_T_CTRL_PINPER;
		writel(val, fep->hwp + FEC_ATIME_CTRL);

		/* Compare channel setting. */
		val = readl(fep->hwp + FEC_TCSR(fep->pps_channel));
		val |= (1 << FEC_T_TF_OFFSET | 1 << FEC_T_TIE_OFFSET);
		val &= ~(1 << FEC_T_TDRE_OFFSET);
		val &= ~(FEC_T_TMODE_MASK);
		val |= (FEC_HIGH_PULSE << FEC_T_TMODE_OFFSET);
		writel(val, fep->hwp + FEC_TCSR(fep->pps_channel));

		/* Write the second compare event timestamp and calculate
		 * the third timestamp. Refer the TCCR register detail in the spec.
		 */
		writel(fep->next_counter, fep->hwp + FEC_TCCR(fep->pps_channel));
		fep->next_counter = (fep->next_counter + fep->reload_period) & fep->cc.mask;
	} else {
		writel(0, fep->hwp + FEC_TCSR(fep->pps_channel));
	}

	fep->pps_enable = enable;
	spin_unlock_irqrestore(&fep->tmreg_lock, flags);

	return 0;
}