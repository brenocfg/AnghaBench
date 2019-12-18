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
struct s5k5baf {TYPE_1__* supplies; int /*<<< orphan*/  sd; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int S5K5BAF_NUM_SUPPLIES ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/ * s5k5baf_supply_names ; 
 int /*<<< orphan*/  v4l2_err (struct i2c_client*,char*) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s5k5baf_configure_regulators(struct s5k5baf *state)
{
	struct i2c_client *c = v4l2_get_subdevdata(&state->sd);
	int ret;
	int i;

	for (i = 0; i < S5K5BAF_NUM_SUPPLIES; i++)
		state->supplies[i].supply = s5k5baf_supply_names[i];

	ret = devm_regulator_bulk_get(&c->dev, S5K5BAF_NUM_SUPPLIES,
				      state->supplies);
	if (ret < 0)
		v4l2_err(c, "failed to get regulators\n");
	return ret;
}