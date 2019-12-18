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
struct intel_quark_mfd {int /*<<< orphan*/  i2c_clk; int /*<<< orphan*/  i2c_clk_lookup; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkdev_drop (int /*<<< orphan*/ ) ; 
 struct intel_quark_mfd* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static void intel_quark_unregister_i2c_clk(struct device *dev)
{
	struct intel_quark_mfd *quark_mfd = dev_get_drvdata(dev);

	if (!quark_mfd->i2c_clk_lookup)
		return;

	clkdev_drop(quark_mfd->i2c_clk_lookup);
	clk_unregister(quark_mfd->i2c_clk);
}