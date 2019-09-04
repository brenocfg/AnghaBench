#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct i2c_mux_core {int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {int n_gpios; scalar_t__* gpios; } ;
struct gpiomux {TYPE_1__ data; scalar_t__ gpio_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (scalar_t__) ; 
 int /*<<< orphan*/  i2c_mux_del_adapters (struct i2c_mux_core*) ; 
 struct gpiomux* i2c_mux_priv (struct i2c_mux_core*) ; 
 int /*<<< orphan*/  i2c_put_adapter (int /*<<< orphan*/ ) ; 
 struct i2c_mux_core* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int i2c_mux_gpio_remove(struct platform_device *pdev)
{
	struct i2c_mux_core *muxc = platform_get_drvdata(pdev);
	struct gpiomux *mux = i2c_mux_priv(muxc);
	int i;

	i2c_mux_del_adapters(muxc);

	for (i = 0; i < mux->data.n_gpios; i++)
		gpio_free(mux->gpio_base + mux->data.gpios[i]);

	i2c_put_adapter(muxc->parent);

	return 0;
}