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
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * W83773_OFFSET_LSB ; 
 int /*<<< orphan*/ * W83773_OFFSET_MSB ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 long temp_of_remote (unsigned int,unsigned int) ; 

__attribute__((used)) static int get_offset(struct regmap *regmap, int index, long *val)
{
	unsigned int regval_high;
	unsigned int regval_low;
	int ret;

	ret = regmap_read(regmap, W83773_OFFSET_MSB[index], &regval_high);
	if (ret < 0)
		return ret;

	ret = regmap_read(regmap, W83773_OFFSET_LSB[index], &regval_low);
	if (ret < 0)
		return ret;

	*val = temp_of_remote(regval_high, regval_low);
	return 0;
}