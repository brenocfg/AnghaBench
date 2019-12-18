#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpr0521_data {int /*<<< orphan*/  regmap; } ;
struct TYPE_4__ {int mask; int shift; TYPE_1__* gain; int /*<<< orphan*/  reg; } ;
struct TYPE_3__ {int scale; int uscale; } ;

/* Variables and functions */
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 TYPE_2__* rpr0521_gain ; 

__attribute__((used)) static int rpr0521_get_gain(struct rpr0521_data *data, int chan,
			    int *val, int *val2)
{
	int ret, reg, idx;

	ret = regmap_read(data->regmap, rpr0521_gain[chan].reg, &reg);
	if (ret < 0)
		return ret;

	idx = (rpr0521_gain[chan].mask & reg) >> rpr0521_gain[chan].shift;
	*val = rpr0521_gain[chan].gain[idx].scale;
	*val2 = rpr0521_gain[chan].gain[idx].uscale;

	return 0;
}