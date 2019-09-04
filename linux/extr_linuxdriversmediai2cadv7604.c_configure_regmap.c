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
struct adv76xx_state {int /*<<< orphan*/ * i2c_clients; int /*<<< orphan*/ * regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * adv76xx_regmap_cnf ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_err (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int configure_regmap(struct adv76xx_state *state, int region)
{
	int err;

	if (!state->i2c_clients[region])
		return -ENODEV;

	state->regmap[region] =
		devm_regmap_init_i2c(state->i2c_clients[region],
				     &adv76xx_regmap_cnf[region]);

	if (IS_ERR(state->regmap[region])) {
		err = PTR_ERR(state->regmap[region]);
		v4l_err(state->i2c_clients[region],
			"Error initializing regmap %d with error %d\n",
			region, err);
		return -EINVAL;
	}

	return 0;
}