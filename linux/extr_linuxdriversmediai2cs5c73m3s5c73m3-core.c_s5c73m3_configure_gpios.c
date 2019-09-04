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
struct s5c73m3_gpio {int /*<<< orphan*/  gpio; scalar_t__ level; } ;
struct s5c73m3 {struct s5c73m3_gpio* gpio; struct i2c_client* i2c_client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int GPIOF_DIR_OUT ; 
 unsigned int GPIOF_INIT_HIGH ; 
 int GPIO_NUM ; 
 int devm_gpio_request_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,char const* const) ; 
 int /*<<< orphan*/  v4l2_err (struct i2c_client*,char*,char const* const) ; 

__attribute__((used)) static int s5c73m3_configure_gpios(struct s5c73m3 *state)
{
	static const char * const gpio_names[] = {
		"S5C73M3_STBY", "S5C73M3_RST"
	};
	struct i2c_client *c = state->i2c_client;
	struct s5c73m3_gpio *g = state->gpio;
	int ret, i;

	for (i = 0; i < GPIO_NUM; ++i) {
		unsigned int flags = GPIOF_DIR_OUT;
		if (g[i].level)
			flags |= GPIOF_INIT_HIGH;
		ret = devm_gpio_request_one(&c->dev, g[i].gpio, flags,
					    gpio_names[i]);
		if (ret) {
			v4l2_err(c, "failed to request gpio %s\n",
				 gpio_names[i]);
			return ret;
		}
	}
	return 0;
}