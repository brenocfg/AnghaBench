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
struct vic {int booted; int /*<<< orphan*/  clk; int /*<<< orphan*/  rst; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct vic* dev_get_drvdata (struct device*) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int vic_runtime_suspend(struct device *dev)
{
	struct vic *vic = dev_get_drvdata(dev);
	int err;

	err = reset_control_assert(vic->rst);
	if (err < 0)
		return err;

	usleep_range(2000, 4000);

	clk_disable_unprepare(vic->clk);

	vic->booted = false;

	return 0;
}