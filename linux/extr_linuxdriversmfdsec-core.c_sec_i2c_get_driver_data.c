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
struct i2c_device_id {unsigned long driver_data; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long sec_i2c_get_driver_data(struct i2c_client *i2c,
						const struct i2c_device_id *id)
{
#ifdef CONFIG_OF
	if (i2c->dev.of_node) {
		const struct of_device_id *match;

		match = of_match_node(sec_dt_match, i2c->dev.of_node);
		return (unsigned long)match->data;
	}
#endif
	return id->driver_data;
}