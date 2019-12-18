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
struct zx_vga {int /*<<< orphan*/  i2c_wclk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct zx_vga* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static void zx_vga_unbind(struct device *dev, struct device *master,
			  void *data)
{
	struct zx_vga *vga = dev_get_drvdata(dev);

	clk_disable_unprepare(vga->i2c_wclk);
}