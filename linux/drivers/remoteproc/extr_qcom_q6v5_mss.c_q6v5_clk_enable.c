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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 

__attribute__((used)) static int q6v5_clk_enable(struct device *dev,
			   struct clk **clks, int count)
{
	int rc;
	int i;

	for (i = 0; i < count; i++) {
		rc = clk_prepare_enable(clks[i]);
		if (rc) {
			dev_err(dev, "Clock enable failed\n");
			goto err;
		}
	}

	return 0;
err:
	for (i--; i >= 0; i--)
		clk_disable_unprepare(clks[i]);

	return rc;
}