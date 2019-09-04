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
struct TYPE_6__ {int num; TYPE_1__* tbl; } ;
struct TYPE_5__ {int /*<<< orphan*/  config_odr_mask; int /*<<< orphan*/  config; } ;
struct TYPE_4__ {int odr; int uodr; int /*<<< orphan*/  bits; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_3__* bmi160_odr_table ; 
 TYPE_2__* bmi160_regs ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int bmi160_set_odr(struct bmi160_data *data, enum bmi160_sensor_type t,
		   int odr, int uodr)
{
	int i;

	for (i = 0; i < bmi160_odr_table[t].num; i++)
		if (bmi160_odr_table[t].tbl[i].odr == odr &&
		    bmi160_odr_table[t].tbl[i].uodr == uodr)
			break;

	if (i >= bmi160_odr_table[t].num)
		return -EINVAL;

	return regmap_update_bits(data->regmap,
				  bmi160_regs[t].config,
				  bmi160_regs[t].config_odr_mask,
				  bmi160_odr_table[t].tbl[i].bits);
}