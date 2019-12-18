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
struct platform_device {int dummy; } ;
struct i2c_mux_core {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_mux_del_adapters (struct i2c_mux_core*) ; 
 int /*<<< orphan*/  i2c_put_adapter (int /*<<< orphan*/ ) ; 
 struct i2c_mux_core* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int i2c_mux_pinctrl_remove(struct platform_device *pdev)
{
	struct i2c_mux_core *muxc = platform_get_drvdata(pdev);

	i2c_mux_del_adapters(muxc);
	i2c_put_adapter(muxc->parent);

	return 0;
}