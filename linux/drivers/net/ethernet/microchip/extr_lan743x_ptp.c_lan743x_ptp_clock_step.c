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
typedef  long long u64 ;
typedef  int u32 ;
struct lan743x_ptp {int /*<<< orphan*/  command_lock; } ;
struct lan743x_adapter {struct lan743x_ptp ptp; } ;
typedef  long long s64 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  PTP_CLOCK_STEP_ADJ ; 
 int PTP_CLOCK_STEP_ADJ_DIR_ ; 
 int PTP_CLOCK_STEP_ADJ_VALUE_MASK_ ; 
 int /*<<< orphan*/  PTP_CMD_CTL ; 
 int PTP_CMD_CTL_PTP_CLK_STP_NSEC_ ; 
 int PTP_CMD_CTL_PTP_CLOCK_STEP_SEC_ ; 
 int div_u64_rem (long long,int,int*) ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lan743x_ptp_clock_get (struct lan743x_adapter*,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lan743x_ptp_clock_set (struct lan743x_adapter*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan743x_ptp_wait_till_cmd_done (struct lan743x_adapter*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lan743x_ptp_clock_step(struct lan743x_adapter *adapter,
				   s64 time_step_ns)
{
	struct lan743x_ptp *ptp = &adapter->ptp;
	u32 nano_seconds_step = 0;
	u64 abs_time_step_ns = 0;
	u32 unsigned_seconds = 0;
	u32 nano_seconds = 0;
	u32 remainder = 0;
	s32 seconds = 0;

	if (time_step_ns >  15000000000LL) {
		/* convert to clock set */
		lan743x_ptp_clock_get(adapter, &unsigned_seconds,
				      &nano_seconds, NULL);
		unsigned_seconds += div_u64_rem(time_step_ns, 1000000000LL,
						&remainder);
		nano_seconds += remainder;
		if (nano_seconds >= 1000000000) {
			unsigned_seconds++;
			nano_seconds -= 1000000000;
		}
		lan743x_ptp_clock_set(adapter, unsigned_seconds,
				      nano_seconds, 0);
		return;
	} else if (time_step_ns < -15000000000LL) {
		/* convert to clock set */
		time_step_ns = -time_step_ns;

		lan743x_ptp_clock_get(adapter, &unsigned_seconds,
				      &nano_seconds, NULL);
		unsigned_seconds -= div_u64_rem(time_step_ns, 1000000000LL,
						&remainder);
		nano_seconds_step = remainder;
		if (nano_seconds < nano_seconds_step) {
			unsigned_seconds--;
			nano_seconds += 1000000000;
		}
		nano_seconds -= nano_seconds_step;
		lan743x_ptp_clock_set(adapter, unsigned_seconds,
				      nano_seconds, 0);
		return;
	}

	/* do clock step */
	if (time_step_ns >= 0) {
		abs_time_step_ns = (u64)(time_step_ns);
		seconds = (s32)div_u64_rem(abs_time_step_ns, 1000000000,
					   &remainder);
		nano_seconds = (u32)remainder;
	} else {
		abs_time_step_ns = (u64)(-time_step_ns);
		seconds = -((s32)div_u64_rem(abs_time_step_ns, 1000000000,
					     &remainder));
		nano_seconds = (u32)remainder;
		if (nano_seconds > 0) {
			/* subtracting nano seconds is not allowed
			 * convert to subtracting from seconds,
			 * and adding to nanoseconds
			 */
			seconds--;
			nano_seconds = (1000000000 - nano_seconds);
		}
	}

	if (nano_seconds > 0) {
		/* add 8 ns to cover the likely normal increment */
		nano_seconds += 8;
	}

	if (nano_seconds >= 1000000000) {
		/* carry into seconds */
		seconds++;
		nano_seconds -= 1000000000;
	}

	while (seconds) {
		mutex_lock(&ptp->command_lock);
		if (seconds > 0) {
			u32 adjustment_value = (u32)seconds;

			if (adjustment_value > 0xF)
				adjustment_value = 0xF;
			lan743x_csr_write(adapter, PTP_CLOCK_STEP_ADJ,
					  PTP_CLOCK_STEP_ADJ_DIR_ |
					  adjustment_value);
			seconds -= ((s32)adjustment_value);
		} else {
			u32 adjustment_value = (u32)(-seconds);

			if (adjustment_value > 0xF)
				adjustment_value = 0xF;
			lan743x_csr_write(adapter, PTP_CLOCK_STEP_ADJ,
					  adjustment_value);
			seconds += ((s32)adjustment_value);
		}
		lan743x_csr_write(adapter, PTP_CMD_CTL,
				  PTP_CMD_CTL_PTP_CLOCK_STEP_SEC_);
		lan743x_ptp_wait_till_cmd_done(adapter,
					       PTP_CMD_CTL_PTP_CLOCK_STEP_SEC_);
		mutex_unlock(&ptp->command_lock);
	}
	if (nano_seconds) {
		mutex_lock(&ptp->command_lock);
		lan743x_csr_write(adapter, PTP_CLOCK_STEP_ADJ,
				  PTP_CLOCK_STEP_ADJ_DIR_ |
				  (nano_seconds &
				  PTP_CLOCK_STEP_ADJ_VALUE_MASK_));
		lan743x_csr_write(adapter, PTP_CMD_CTL,
				  PTP_CMD_CTL_PTP_CLK_STP_NSEC_);
		lan743x_ptp_wait_till_cmd_done(adapter,
					       PTP_CMD_CTL_PTP_CLK_STP_NSEC_);
		mutex_unlock(&ptp->command_lock);
	}
}