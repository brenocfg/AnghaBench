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
typedef  scalar_t__ u16 ;
struct TYPE_4__ {int speed; } ;
struct TYPE_3__ {scalar_t__ num_vfs; } ;
struct fm10k_hw {TYPE_2__ bus; TYPE_1__ iov; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 int /*<<< orphan*/  FM10K_TC_CREDIT (scalar_t__) ; 
 int /*<<< orphan*/  FM10K_TC_MAXCREDIT (scalar_t__) ; 
 int FM10K_TC_MAXCREDIT_64K ; 
 int /*<<< orphan*/  FM10K_TC_RATE (scalar_t__) ; 
 int FM10K_TC_RATE_INTERVAL_4US_GEN1 ; 
 int FM10K_TC_RATE_INTERVAL_4US_GEN2 ; 
 int FM10K_TC_RATE_INTERVAL_4US_GEN3 ; 
 int FM10K_TC_RATE_QUANTA_MASK ; 
 int FM10K_VF_TC_MAX ; 
 int FM10K_VF_TC_MIN ; 
#define  fm10k_bus_speed_2500 129 
#define  fm10k_bus_speed_5000 128 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 fm10k_iov_configure_tc_pf(struct fm10k_hw *hw, u16 vf_idx, int rate)
{
	/* configure defaults */
	u32 interval = FM10K_TC_RATE_INTERVAL_4US_GEN3;
	u32 tc_rate = FM10K_TC_RATE_QUANTA_MASK;

	/* verify vf is in range */
	if (vf_idx >= hw->iov.num_vfs)
		return FM10K_ERR_PARAM;

	/* set interval to align with 4.096 usec in all modes */
	switch (hw->bus.speed) {
	case fm10k_bus_speed_2500:
		interval = FM10K_TC_RATE_INTERVAL_4US_GEN1;
		break;
	case fm10k_bus_speed_5000:
		interval = FM10K_TC_RATE_INTERVAL_4US_GEN2;
		break;
	default:
		break;
	}

	if (rate) {
		if (rate > FM10K_VF_TC_MAX || rate < FM10K_VF_TC_MIN)
			return FM10K_ERR_PARAM;

		/* The quanta is measured in Bytes per 4.096 or 8.192 usec
		 * The rate is provided in Mbits per second
		 * To tralslate from rate to quanta we need to multiply the
		 * rate by 8.192 usec and divide by 8 bits/byte.  To avoid
		 * dealing with floating point we can round the values up
		 * to the nearest whole number ratio which gives us 128 / 125.
		 */
		tc_rate = (rate * 128) / 125;

		/* try to keep the rate limiting accurate by increasing
		 * the number of credits and interval for rates less than 4Gb/s
		 */
		if (rate < 4000)
			interval <<= 1;
		else
			tc_rate >>= 1;
	}

	/* update rate limiter with new values */
	fm10k_write_reg(hw, FM10K_TC_RATE(vf_idx), tc_rate | interval);
	fm10k_write_reg(hw, FM10K_TC_MAXCREDIT(vf_idx), FM10K_TC_MAXCREDIT_64K);
	fm10k_write_reg(hw, FM10K_TC_CREDIT(vf_idx), FM10K_TC_MAXCREDIT_64K);

	return 0;
}