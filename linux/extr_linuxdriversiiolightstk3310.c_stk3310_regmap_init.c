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
struct stk3310_data {struct regmap* regmap; struct i2c_client* client; } ;
struct regmap {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  STK3310_REGFIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  als_gain ; 
 int /*<<< orphan*/  als_it ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flag_nf ; 
 int /*<<< orphan*/  flag_psint ; 
 int /*<<< orphan*/  int_ps ; 
 int /*<<< orphan*/  ps_gain ; 
 int /*<<< orphan*/  ps_it ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/  stk3310_regmap_config ; 

__attribute__((used)) static int stk3310_regmap_init(struct stk3310_data *data)
{
	struct regmap *regmap;
	struct i2c_client *client;

	client = data->client;
	regmap = devm_regmap_init_i2c(client, &stk3310_regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(&client->dev, "regmap initialization failed.\n");
		return PTR_ERR(regmap);
	}
	data->regmap = regmap;

	STK3310_REGFIELD(state);
	STK3310_REGFIELD(als_gain);
	STK3310_REGFIELD(ps_gain);
	STK3310_REGFIELD(als_it);
	STK3310_REGFIELD(ps_it);
	STK3310_REGFIELD(int_ps);
	STK3310_REGFIELD(flag_psint);
	STK3310_REGFIELD(flag_nf);

	return 0;
}