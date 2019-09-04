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
typedef  int u32 ;
struct TYPE_3__ {int num_lanes; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct tc_data {int /*<<< orphan*/  dev; TYPE_2__ link; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP0CTL ; 
 int /*<<< orphan*/  DP0_LTLOOPCTRL ; 
 int /*<<< orphan*/  DP0_LTSTAT ; 
 int /*<<< orphan*/  DP0_SNKLTCTRL ; 
 int /*<<< orphan*/  DP0_SRCCTRL ; 
 int DP0_SRCCTRL_AUTOCORRECT ; 
 int DP0_SRCCTRL_SCRMBLDIS ; 
 int DP0_SRCCTRL_TP1 ; 
 int DP0_SRCCTRL_TP2 ; 
 int DP_EN ; 
 int DP_LINK_SCRAMBLING_DISABLE ; 
 int DP_TRAINING_PATTERN_1 ; 
 int DP_TRAINING_PATTERN_2 ; 
 int LT_CHANNEL0_EQ_BITS ; 
 int LT_CHANNEL1_EQ_BITS ; 
 int LT_INTERLANE_ALIGN_DONE ; 
 int LT_LOOPDONE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,char const* const) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  tc_read (int /*<<< orphan*/ ,int*) ; 
 int tc_srcctrl (struct tc_data*) ; 
 int /*<<< orphan*/  tc_write (int /*<<< orphan*/ ,int) ; 
 char** training_pattern1_errors ; 
 char** training_pattern2_errors ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tc_link_training(struct tc_data *tc, int pattern)
{
	const char * const *errors;
	u32 srcctrl = tc_srcctrl(tc) | DP0_SRCCTRL_SCRMBLDIS |
		      DP0_SRCCTRL_AUTOCORRECT;
	int timeout;
	int retry;
	u32 value;
	int ret;

	if (pattern == DP_TRAINING_PATTERN_1) {
		srcctrl |= DP0_SRCCTRL_TP1;
		errors = training_pattern1_errors;
	} else {
		srcctrl |= DP0_SRCCTRL_TP2;
		errors = training_pattern2_errors;
	}

	/* Set DPCD 0x102 for Training Part 1 or 2 */
	tc_write(DP0_SNKLTCTRL, DP_LINK_SCRAMBLING_DISABLE | pattern);

	tc_write(DP0_LTLOOPCTRL,
		 (0x0f << 28) |	/* Defer Iteration Count */
		 (0x0f << 24) |	/* Loop Iteration Count */
		 (0x0d << 0));	/* Loop Timer Delay */

	retry = 5;
	do {
		/* Set DP0 Training Pattern */
		tc_write(DP0_SRCCTRL, srcctrl);

		/* Enable DP0 to start Link Training */
		tc_write(DP0CTL, DP_EN);

		/* wait */
		timeout = 1000;
		do {
			tc_read(DP0_LTSTAT, &value);
			udelay(1);
		} while ((!(value & LT_LOOPDONE)) && (--timeout));
		if (timeout == 0) {
			dev_err(tc->dev, "Link training timeout!\n");
		} else {
			int pattern = (value >> 11) & 0x3;
			int error = (value >> 8) & 0x7;

			dev_dbg(tc->dev,
				"Link training phase %d done after %d uS: %s\n",
				pattern, 1000 - timeout, errors[error]);
			if (pattern == DP_TRAINING_PATTERN_1 && error == 0)
				break;
			if (pattern == DP_TRAINING_PATTERN_2) {
				value &= LT_CHANNEL1_EQ_BITS |
					 LT_INTERLANE_ALIGN_DONE |
					 LT_CHANNEL0_EQ_BITS;
				/* in case of two lanes */
				if ((tc->link.base.num_lanes == 2) &&
				    (value == (LT_CHANNEL1_EQ_BITS |
					       LT_INTERLANE_ALIGN_DONE |
					       LT_CHANNEL0_EQ_BITS)))
					break;
				/* in case of one line */
				if ((tc->link.base.num_lanes == 1) &&
				    (value == (LT_INTERLANE_ALIGN_DONE |
					       LT_CHANNEL0_EQ_BITS)))
					break;
			}
		}
		/* restart */
		tc_write(DP0CTL, 0);
		usleep_range(10, 20);
	} while (--retry);
	if (retry == 0) {
		dev_err(tc->dev, "Failed to finish training phase %d\n",
			pattern);
	}

	return 0;
err:
	return ret;
}