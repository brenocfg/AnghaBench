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
struct hideep_ts {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HIDEEP_FLASH_STA ; 
 int hideep_pgm_r_reg (struct hideep_ts*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int hideep_check_status(struct hideep_ts *ts)
{
	int time_out = 100;
	int status;
	int error;

	while (time_out--) {
		error = hideep_pgm_r_reg(ts, HIDEEP_FLASH_STA, &status);
		if (!error && status)
			return 0;

		usleep_range(1000, 1100);
	}

	return -ETIMEDOUT;
}