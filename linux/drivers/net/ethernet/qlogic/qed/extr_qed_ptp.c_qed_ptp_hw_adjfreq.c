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
typedef  int u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {struct qed_ptt* p_ptp_ptt; } ;
struct qed_dev {int dummy; } ;
typedef  int s64 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qed_hwfn*,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NIG_REG_TSGEN_DRIFT_CNTR_CONF ; 
 int /*<<< orphan*/  NIG_REG_TSGEN_RST_DRIFT_CNTR ; 
 int QED_DRIFT_CNTR_ADJUSTMENT_SHIFT ; 
 int QED_DRIFT_CNTR_DIRECTION_SHIFT ; 
 int QED_DRIFT_CNTR_TIME_QUANTA_SHIFT ; 
 struct qed_hwfn* QED_LEADING_HWFN (struct qed_dev*) ; 
 int div_s64 (int,int) ; 
 int qed_rd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qed_ptp_hw_adjfreq(struct qed_dev *cdev, s32 ppb)
{
	s64 best_val = 0, val, best_period = 0, period, approx_dev, dif, dif2;
	struct qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	struct qed_ptt *p_ptt = p_hwfn->p_ptp_ptt;
	u32 drift_ctr_cfg = 0, drift_state;
	int drift_dir = 1;

	if (ppb < 0) {
		ppb = -ppb;
		drift_dir = 0;
	}

	if (ppb > 1) {
		s64 best_dif = ppb, best_approx_dev = 1;

		/* Adjustment value is up to +/-7ns, find an optimal value in
		 * this range.
		 */
		for (val = 7; val > 0; val--) {
			period = div_s64(val * 1000000000, ppb);
			period -= 8;
			period >>= 4;
			if (period < 1)
				period = 1;
			if (period > 0xFFFFFFE)
				period = 0xFFFFFFE;

			/* Check both rounding ends for approximate error */
			approx_dev = period * 16 + 8;
			dif = ppb * approx_dev - val * 1000000000;
			dif2 = dif + 16 * ppb;

			if (dif < 0)
				dif = -dif;
			if (dif2 < 0)
				dif2 = -dif2;

			/* Determine which end gives better approximation */
			if (dif * (approx_dev + 16) > dif2 * approx_dev) {
				period++;
				approx_dev += 16;
				dif = dif2;
			}

			/* Track best approximation found so far */
			if (best_dif * approx_dev > dif * best_approx_dev) {
				best_dif = dif;
				best_val = val;
				best_period = period;
				best_approx_dev = approx_dev;
			}
		}
	} else if (ppb == 1) {
		/* This is a special case as its the only value which wouldn't
		 * fit in a s64 variable. In order to prevent castings simple
		 * handle it seperately.
		 */
		best_val = 4;
		best_period = 0xee6b27f;
	} else {
		best_val = 0;
		best_period = 0xFFFFFFF;
	}

	drift_ctr_cfg = (best_period << QED_DRIFT_CNTR_TIME_QUANTA_SHIFT) |
			(((int)best_val) << QED_DRIFT_CNTR_ADJUSTMENT_SHIFT) |
			(((int)drift_dir) << QED_DRIFT_CNTR_DIRECTION_SHIFT);

	qed_wr(p_hwfn, p_ptt, NIG_REG_TSGEN_RST_DRIFT_CNTR, 0x1);

	drift_state = qed_rd(p_hwfn, p_ptt, NIG_REG_TSGEN_RST_DRIFT_CNTR);
	if (drift_state & 1) {
		qed_wr(p_hwfn, p_ptt, NIG_REG_TSGEN_DRIFT_CNTR_CONF,
		       drift_ctr_cfg);
	} else {
		DP_INFO(p_hwfn, "Drift counter is not reset\n");
		return -EINVAL;
	}

	qed_wr(p_hwfn, p_ptt, NIG_REG_TSGEN_RST_DRIFT_CNTR, 0x0);

	return 0;
}