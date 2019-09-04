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
struct regmap_config {int val_bits; int reg_bits; } ;
struct regmap_bus {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUPP ; 
 struct regmap_bus const* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct regmap_bus const regmap_sccb_bus ; 
 scalar_t__ sccb_is_available (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct regmap_bus *regmap_get_sccb_bus(struct i2c_client *i2c,
					const struct regmap_config *config)
{
	if (config->val_bits == 8 && config->reg_bits == 8 &&
			sccb_is_available(i2c->adapter))
		return &regmap_sccb_bus;

	return ERR_PTR(-ENOTSUPP);
}