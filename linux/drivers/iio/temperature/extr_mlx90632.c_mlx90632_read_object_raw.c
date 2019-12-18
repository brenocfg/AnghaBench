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
typedef  int /*<<< orphan*/  u8 ;
struct regmap {int dummy; } ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  MLX90632_RAM_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX90632_RAM_2 (int /*<<< orphan*/ ) ; 
 int mlx90632_channel_new_select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int mlx90632_read_object_raw(struct regmap *regmap,
				    int perform_measurement_ret,
				    s16 *object_new_raw, s16 *object_old_raw)
{
	int ret;
	unsigned int read_tmp;
	s16 read;
	u8 channel = 0;
	u8 channel_old = 0;

	ret = mlx90632_channel_new_select(perform_measurement_ret, &channel,
					  &channel_old);
	if (ret != 0)
		return ret;

	ret = regmap_read(regmap, MLX90632_RAM_2(channel), &read_tmp);
	if (ret < 0)
		return ret;

	read = (s16)read_tmp;

	ret = regmap_read(regmap, MLX90632_RAM_1(channel), &read_tmp);
	if (ret < 0)
		return ret;
	*object_new_raw = (read + (s16)read_tmp) / 2;

	ret = regmap_read(regmap, MLX90632_RAM_2(channel_old), &read_tmp);
	if (ret < 0)
		return ret;
	read = (s16)read_tmp;

	ret = regmap_read(regmap, MLX90632_RAM_1(channel_old), &read_tmp);
	if (ret < 0)
		return ret;
	*object_old_raw = (read + (s16)read_tmp) / 2;

	return ret;
}