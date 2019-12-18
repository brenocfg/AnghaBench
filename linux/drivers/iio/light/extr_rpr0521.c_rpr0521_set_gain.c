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
struct TYPE_4__ {int size; int shift; int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; TYPE_1__* gain; } ;
struct TYPE_3__ {int scale; int uscale; } ;

/* Variables and functions */
 int EINVAL ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* rpr0521_gain ; 

__attribute__((used)) static int rpr0521_set_gain(struct rpr0521_data *data, int chan,
			    int val, int val2)
{
	int i, idx = -EINVAL;

	/* get gain index */
	for (i = 0; i < rpr0521_gain[chan].size; i++)
		if (val == rpr0521_gain[chan].gain[i].scale &&
		    val2 == rpr0521_gain[chan].gain[i].uscale) {
			idx = i;
			break;
		}

	if (idx < 0)
		return idx;

	return regmap_update_bits(data->regmap, rpr0521_gain[chan].reg,
				  rpr0521_gain[chan].mask,
				  idx << rpr0521_gain[chan].shift);
}