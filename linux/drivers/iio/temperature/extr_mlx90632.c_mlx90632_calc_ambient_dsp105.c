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
struct mlx90632_data {int /*<<< orphan*/  regmap; } ;
typedef  scalar_t__ s32 ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int /*<<< orphan*/  MLX90632_EE_Gb ; 
 int /*<<< orphan*/  MLX90632_EE_P_G ; 
 int /*<<< orphan*/  MLX90632_EE_P_O ; 
 int /*<<< orphan*/  MLX90632_EE_P_R ; 
 int /*<<< orphan*/  MLX90632_EE_P_T ; 
 int mlx90632_calc_temp_ambient (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ mlx90632_read_ambient_raw (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 scalar_t__ mlx90632_read_ee_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int mlx90632_calc_ambient_dsp105(struct mlx90632_data *data, int *val)
{
	s32 ret;
	unsigned int read_tmp;
	s32 PT, PR, PG, PO;
	s16 Gb;
	s16 ambient_new_raw, ambient_old_raw;

	ret = mlx90632_read_ee_register(data->regmap, MLX90632_EE_P_R, &PR);
	if (ret < 0)
		return ret;
	ret = mlx90632_read_ee_register(data->regmap, MLX90632_EE_P_G, &PG);
	if (ret < 0)
		return ret;
	ret = mlx90632_read_ee_register(data->regmap, MLX90632_EE_P_T, &PT);
	if (ret < 0)
		return ret;
	ret = mlx90632_read_ee_register(data->regmap, MLX90632_EE_P_O, &PO);
	if (ret < 0)
		return ret;
	ret = regmap_read(data->regmap, MLX90632_EE_Gb, &read_tmp);
	if (ret < 0)
		return ret;
	Gb = (s16)read_tmp;

	ret = mlx90632_read_ambient_raw(data->regmap, &ambient_new_raw,
					&ambient_old_raw);
	if (ret < 0)
		return ret;
	*val = mlx90632_calc_temp_ambient(ambient_new_raw, ambient_old_raw,
					  PT, PR, PG, PO, Gb);
	return ret;
}