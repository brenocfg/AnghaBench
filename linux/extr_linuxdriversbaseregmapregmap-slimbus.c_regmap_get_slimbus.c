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
struct slim_device {int dummy; } ;
struct regmap_config {int val_bits; int reg_bits; } ;
struct regmap_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUPP ; 
 struct regmap_bus const* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct regmap_bus const regmap_slimbus_bus ; 

__attribute__((used)) static const struct regmap_bus *regmap_get_slimbus(struct slim_device *slim,
					const struct regmap_config *config)
{
	if (config->val_bits == 8 && config->reg_bits == 16)
		return &regmap_slimbus_bus;

	return ERR_PTR(-ENOTSUPP);
}