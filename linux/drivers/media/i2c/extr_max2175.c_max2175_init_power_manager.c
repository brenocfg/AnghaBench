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
struct max2175 {int dummy; } ;

/* Variables and functions */
 int max2175_poll_timeout (struct max2175*,int,int,int,int,int) ; 
 int /*<<< orphan*/  max2175_write_bit (struct max2175*,int,int,int) ; 
 int /*<<< orphan*/  mxm_err (struct max2175*,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int max2175_init_power_manager(struct max2175 *ctx)
{
	int ret;

	/* Execute on-chip power-up/calibration */
	max2175_write_bit(ctx, 99, 2, 0);
	usleep_range(1000, 1500);
	max2175_write_bit(ctx, 99, 2, 1);

	/* Wait for the power manager to finish. */
	ret = max2175_poll_timeout(ctx, 69, 7, 7, 1, 50000);
	if (ret)
		mxm_err(ctx, "init pm failed\n");

	return ret;
}