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
struct s5k5baf_gpio {int /*<<< orphan*/  gpio; scalar_t__ level; } ;
struct s5k5baf {struct s5k5baf_gpio* gpios; int /*<<< orphan*/  sd; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int GPIOF_DIR_OUT ; 
 int GPIOF_INIT_HIGH ; 
 int NUM_GPIOS ; 
 int devm_gpio_request_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char const* const) ; 
 int /*<<< orphan*/  v4l2_err (struct i2c_client*,char*,char const* const) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s5k5baf_configure_gpios(struct s5k5baf *state)
{
	static const char * const name[] = { "S5K5BAF_STBY", "S5K5BAF_RST" };
	struct i2c_client *c = v4l2_get_subdevdata(&state->sd);
	struct s5k5baf_gpio *g = state->gpios;
	int ret, i;

	for (i = 0; i < NUM_GPIOS; ++i) {
		int flags = GPIOF_DIR_OUT;
		if (g[i].level)
			flags |= GPIOF_INIT_HIGH;
		ret = devm_gpio_request_one(&c->dev, g[i].gpio, flags, name[i]);
		if (ret < 0) {
			v4l2_err(c, "failed to request gpio %s\n", name[i]);
			return ret;
		}
	}
	return 0;
}