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
typedef  size_t u8 ;
struct tps65910 {int dummy; } ;
struct comparator {int uV_max; int* vsel_table; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int tps65910_reg_write (struct tps65910*,int /*<<< orphan*/ ,size_t) ; 
 struct comparator* tps_comparators ; 

__attribute__((used)) static int comp_threshold_set(struct tps65910 *tps65910, int id, int voltage)
{
	struct comparator tps_comp = tps_comparators[id];
	int curr_voltage = 0;
	int ret;
	u8 index = 0, val;

	while (curr_voltage < tps_comp.uV_max) {
		curr_voltage = tps_comp.vsel_table[index];
		if (curr_voltage >= voltage)
			break;
		else if (curr_voltage < voltage)
			index ++;
	}

	if (curr_voltage > tps_comp.uV_max)
		return -EINVAL;

	val = index << 1;
	ret = tps65910_reg_write(tps65910, tps_comp.reg, val);

	return ret;
}