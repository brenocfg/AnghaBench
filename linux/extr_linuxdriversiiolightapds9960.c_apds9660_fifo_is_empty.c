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
struct apds9960_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  APDS9960_REG_GFLVL ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline int apds9660_fifo_is_empty(struct apds9960_data *data)
{
	int cnt;
	int ret;

	ret = regmap_read(data->regmap, APDS9960_REG_GFLVL, &cnt);
	if (ret)
		return ret;

	return cnt;
}