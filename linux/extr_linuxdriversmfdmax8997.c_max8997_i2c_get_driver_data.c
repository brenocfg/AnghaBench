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
struct of_device_id {scalar_t__ data; } ;
struct i2c_device_id {unsigned long driver_data; } ;
struct TYPE_2__ {scalar_t__ of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max8997_pmic_dt_match ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline unsigned long max8997_i2c_get_driver_data(struct i2c_client *i2c,
						const struct i2c_device_id *id)
{
	if (IS_ENABLED(CONFIG_OF) && i2c->dev.of_node) {
		const struct of_device_id *match;
		match = of_match_node(max8997_pmic_dt_match, i2c->dev.of_node);
		return (unsigned long)match->data;
	}
	return id->driver_data;
}