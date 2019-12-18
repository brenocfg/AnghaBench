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
struct lm90_data {int max_convrate; int /*<<< orphan*/  update_interval; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (unsigned int,int) ; 
 int LM90_MAX_CONVRATE_MS ; 
 int lm90_write_convrate (struct lm90_data*,int) ; 

__attribute__((used)) static int lm90_set_convrate(struct i2c_client *client, struct lm90_data *data,
			     unsigned int interval)
{
	unsigned int update_interval;
	int i, err;

	/* Shift calculations to avoid rounding errors */
	interval <<= 6;

	/* find the nearest update rate */
	for (i = 0, update_interval = LM90_MAX_CONVRATE_MS << 6;
	     i < data->max_convrate; i++, update_interval >>= 1)
		if (interval >= update_interval * 3 / 4)
			break;

	err = lm90_write_convrate(data, i);
	data->update_interval = DIV_ROUND_CLOSEST(update_interval, 64);
	return err;
}