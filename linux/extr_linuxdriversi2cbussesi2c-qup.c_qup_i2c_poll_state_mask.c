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
struct qup_i2c_dev {scalar_t__ base; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ QUP_STATE ; 
 int QUP_STATE_VALID ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int qup_i2c_poll_state_mask(struct qup_i2c_dev *qup,
				   u32 req_state, u32 req_mask)
{
	int retries = 1;
	u32 state;

	/*
	 * State transition takes 3 AHB clocks cycles + 3 I2C master clock
	 * cycles. So retry once after a 1uS delay.
	 */
	do {
		state = readl(qup->base + QUP_STATE);

		if (state & QUP_STATE_VALID &&
		    (state & req_mask) == req_state)
			return 0;

		udelay(1);
	} while (retries--);

	return -ETIMEDOUT;
}