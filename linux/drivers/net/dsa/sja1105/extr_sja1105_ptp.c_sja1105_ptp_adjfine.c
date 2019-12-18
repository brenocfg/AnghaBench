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
struct TYPE_2__ {scalar_t__ mult; } ;
struct sja1105_private {int /*<<< orphan*/  ptp_lock; TYPE_1__ tstamp_cc; int /*<<< orphan*/  tstamp_tc; } ;
struct ptp_clock_info {int dummy; } ;
typedef  int s64 ;

/* Variables and functions */
 scalar_t__ SJA1105_CC_MULT ; 
 int /*<<< orphan*/  SJA1105_CC_MULT_DEM ; 
 int SJA1105_CC_MULT_NUM ; 
 int div_s64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sja1105_private* ptp_to_sja1105 (struct ptp_clock_info*) ; 
 int /*<<< orphan*/  timecounter_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sja1105_ptp_adjfine(struct ptp_clock_info *ptp, long scaled_ppm)
{
	struct sja1105_private *priv = ptp_to_sja1105(ptp);
	s64 clkrate;

	clkrate = (s64)scaled_ppm * SJA1105_CC_MULT_NUM;
	clkrate = div_s64(clkrate, SJA1105_CC_MULT_DEM);

	mutex_lock(&priv->ptp_lock);

	/* Force a readout to update the timer *before* changing its frequency.
	 *
	 * This way, its corrected time curve can at all times be modeled
	 * as a linear "A * x + B" function, where:
	 *
	 * - B are past frequency adjustments and offset shifts, all
	 *   accumulated into the cycle_last variable.
	 *
	 * - A is the new frequency adjustments we're just about to set.
	 *
	 * Reading now makes B accumulate the correct amount of time,
	 * corrected at the old rate, before changing it.
	 *
	 * Hardware timestamps then become simple points on the curve and
	 * are approximated using the above function.  This is still better
	 * than letting the switch take the timestamps using the hardware
	 * rate-corrected clock (PTPCLKVAL) - the comparison in this case would
	 * be that we're shifting the ruler at the same time as we're taking
	 * measurements with it.
	 *
	 * The disadvantage is that it's possible to receive timestamps when
	 * a frequency adjustment took place in the near past.
	 * In this case they will be approximated using the new ppb value
	 * instead of a compound function made of two segments (one at the old
	 * and the other at the new rate) - introducing some inaccuracy.
	 */
	timecounter_read(&priv->tstamp_tc);

	priv->tstamp_cc.mult = SJA1105_CC_MULT + clkrate;

	mutex_unlock(&priv->ptp_lock);

	return 0;
}