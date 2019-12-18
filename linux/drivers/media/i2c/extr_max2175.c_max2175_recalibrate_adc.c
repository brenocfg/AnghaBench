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
 int /*<<< orphan*/  max2175_write (struct max2175*,int,int) ; 
 int /*<<< orphan*/  mxm_err (struct max2175*,char*) ; 

__attribute__((used)) static int max2175_recalibrate_adc(struct max2175 *ctx)
{
	int ret;

	/* ADC Re-calibration */
	max2175_write(ctx, 150, 0xff);
	max2175_write(ctx, 205, 0xff);
	max2175_write(ctx, 147, 0x20);
	max2175_write(ctx, 147, 0x00);
	max2175_write(ctx, 202, 0x20);
	max2175_write(ctx, 202, 0x00);

	ret = max2175_poll_timeout(ctx, 69, 4, 3, 3, 50000);
	if (ret)
		mxm_err(ctx, "adc recalibration failed\n");

	return ret;
}