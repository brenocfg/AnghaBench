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
typedef  int /*<<< orphan*/  u8 ;
struct nct7802_data {int /*<<< orphan*/  access_lock; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_CLOSEST (unsigned int,unsigned long) ; 
 unsigned long clamp_val (unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int nct7802_write_fan_min(struct nct7802_data *data, u8 reg_fan_low,
				 u8 reg_fan_high, unsigned long limit)
{
	int err;

	if (limit)
		limit = DIV_ROUND_CLOSEST(1350000U, limit);
	else
		limit = 0x1fff;
	limit = clamp_val(limit, 0, 0x1fff);

	mutex_lock(&data->access_lock);
	err = regmap_write(data->regmap, reg_fan_low, limit & 0xff);
	if (err < 0)
		goto abort;

	err = regmap_write(data->regmap, reg_fan_high, (limit & 0x1f00) >> 5);
abort:
	mutex_unlock(&data->access_lock);
	return err;
}