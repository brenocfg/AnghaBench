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
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsc2004_cmd ; 
 int /*<<< orphan*/  tsc2004_input_id ; 
 int tsc200x_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsc200x_regmap_config ; 

__attribute__((used)) static int tsc2004_probe(struct i2c_client *i2c,
			 const struct i2c_device_id *id)

{
	return tsc200x_probe(&i2c->dev, i2c->irq, &tsc2004_input_id,
			     devm_regmap_init_i2c(i2c, &tsc200x_regmap_config),
			     tsc2004_cmd);
}