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
struct device {int dummy; } ;
struct camss_clock {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 

int camss_enable_clocks(int nclocks, struct camss_clock *clock,
			struct device *dev)
{
	int ret;
	int i;

	for (i = 0; i < nclocks; i++) {
		ret = clk_prepare_enable(clock[i].clk);
		if (ret) {
			dev_err(dev, "clock enable failed: %d\n", ret);
			goto error;
		}
	}

	return 0;

error:
	for (i--; i >= 0; i--)
		clk_disable_unprepare(clock[i].clk);

	return ret;
}