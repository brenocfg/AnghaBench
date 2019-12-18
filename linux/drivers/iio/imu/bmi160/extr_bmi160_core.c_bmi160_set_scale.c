#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bmi160_data {int /*<<< orphan*/  regmap; } ;
typedef  enum bmi160_sensor_type { ____Placeholder_bmi160_sensor_type } bmi160_sensor_type ;
struct TYPE_6__ {int /*<<< orphan*/  range; } ;
struct TYPE_5__ {int num; TYPE_1__* tbl; } ;
struct TYPE_4__ {int uscale; int /*<<< orphan*/  bits; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_3__* bmi160_regs ; 
 TYPE_2__* bmi160_scale_table ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int bmi160_set_scale(struct bmi160_data *data, enum bmi160_sensor_type t,
		     int uscale)
{
	int i;

	for (i = 0; i < bmi160_scale_table[t].num; i++)
		if (bmi160_scale_table[t].tbl[i].uscale == uscale)
			break;

	if (i == bmi160_scale_table[t].num)
		return -EINVAL;

	return regmap_write(data->regmap, bmi160_regs[t].range,
			    bmi160_scale_table[t].tbl[i].bits);
}