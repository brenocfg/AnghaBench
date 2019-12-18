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
struct tps65910 {int dummy; } ;
struct comparator {int* vsel_table; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int tps65910_reg_read (struct tps65910*,int /*<<< orphan*/ ,unsigned int*) ; 
 struct comparator* tps_comparators ; 

__attribute__((used)) static int comp_threshold_get(struct tps65910 *tps65910, int id)
{
	struct comparator tps_comp = tps_comparators[id];
	unsigned int val;
	int ret;

	ret = tps65910_reg_read(tps65910, tps_comp.reg, &val);
	if (ret < 0)
		return ret;

	val >>= 1;
	return tps_comp.vsel_table[val];
}