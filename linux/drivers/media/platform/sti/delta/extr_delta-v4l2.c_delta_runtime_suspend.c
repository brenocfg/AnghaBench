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
struct delta_dev {scalar_t__ clk_delta; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 struct delta_dev* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int delta_runtime_suspend(struct device *dev)
{
	struct delta_dev *delta = dev_get_drvdata(dev);

	if (delta->clk_delta)
		clk_disable_unprepare(delta->clk_delta);

	return 0;
}