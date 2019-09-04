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
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int /*<<< orphan*/  MLX90632_RAM_3 (int) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int mlx90632_read_ambient_raw(struct regmap *regmap,
				     s16 *ambient_new_raw, s16 *ambient_old_raw)
{
	int ret;
	unsigned int read_tmp;

	ret = regmap_read(regmap, MLX90632_RAM_3(1), &read_tmp);
	if (ret < 0)
		return ret;
	*ambient_new_raw = (s16)read_tmp;

	ret = regmap_read(regmap, MLX90632_RAM_3(2), &read_tmp);
	if (ret < 0)
		return ret;
	*ambient_old_raw = (s16)read_tmp;

	return ret;
}