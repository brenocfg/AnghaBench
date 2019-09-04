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
struct lg4573 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DCS_ENTER_SLEEP_MODE ; 
 int /*<<< orphan*/  MIPI_DCS_SET_DISPLAY_OFF ; 
 int lg4573_spi_write_dcs (struct lg4573*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int lg4573_display_off(struct lg4573 *ctx)
{
	int ret;

	ret = lg4573_spi_write_dcs(ctx, MIPI_DCS_SET_DISPLAY_OFF);
	if (ret)
		return ret;

	msleep(120);

	return lg4573_spi_write_dcs(ctx, MIPI_DCS_ENTER_SLEEP_MODE);
}