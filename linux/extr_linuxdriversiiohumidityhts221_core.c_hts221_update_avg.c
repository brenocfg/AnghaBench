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
typedef  scalar_t__ u16 ;
struct hts221_hw {TYPE_1__* sensors; int /*<<< orphan*/  regmap; } ;
struct hts221_avg {scalar_t__* avg_avl; int mask; int /*<<< orphan*/  addr; } ;
typedef  enum hts221_sensor_type { ____Placeholder_hts221_sensor_type } hts221_sensor_type ;
struct TYPE_2__ {int cur_avg_idx; } ;

/* Variables and functions */
 int EINVAL ; 
 int HTS221_AVG_DEPTH ; 
 int __ffs (int) ; 
 struct hts221_avg* hts221_avg_list ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int hts221_update_avg(struct hts221_hw *hw,
			     enum hts221_sensor_type type,
			     u16 val)
{
	const struct hts221_avg *avg = &hts221_avg_list[type];
	int i, err, data;

	for (i = 0; i < HTS221_AVG_DEPTH; i++)
		if (avg->avg_avl[i] == val)
			break;

	if (i == HTS221_AVG_DEPTH)
		return -EINVAL;

	data = ((i << __ffs(avg->mask)) & avg->mask);
	err = regmap_update_bits(hw->regmap, avg->addr,
				 avg->mask, data);
	if (err < 0)
		return err;

	hw->sensors[type].cur_avg_idx = i;

	return 0;
}