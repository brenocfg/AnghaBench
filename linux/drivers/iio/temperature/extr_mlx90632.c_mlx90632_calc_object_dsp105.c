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
struct mlx90632_data {int /*<<< orphan*/  emissivity; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  scalar_t__ s32 ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int /*<<< orphan*/  MLX90632_EE_Ea ; 
 int /*<<< orphan*/  MLX90632_EE_Eb ; 
 int /*<<< orphan*/  MLX90632_EE_Fa ; 
 int /*<<< orphan*/  MLX90632_EE_Fb ; 
 int /*<<< orphan*/  MLX90632_EE_Ga ; 
 int /*<<< orphan*/  MLX90632_EE_Gb ; 
 int /*<<< orphan*/  MLX90632_EE_Ha ; 
 int /*<<< orphan*/  MLX90632_EE_Hb ; 
 int /*<<< orphan*/  MLX90632_EE_Ka ; 
 int mlx90632_calc_temp_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx90632_preprocess_temp_amb (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mlx90632_preprocess_temp_obj (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ mlx90632_read_all_channel (struct mlx90632_data*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ mlx90632_read_ee_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int mlx90632_calc_object_dsp105(struct mlx90632_data *data, int *val)
{
	s32 ret;
	s32 Ea, Eb, Fa, Fb, Ga;
	unsigned int read_tmp;
	s16 Ha, Hb, Gb, Ka;
	s16 ambient_new_raw, ambient_old_raw, object_new_raw, object_old_raw;
	s64 object, ambient;

	ret = mlx90632_read_ee_register(data->regmap, MLX90632_EE_Ea, &Ea);
	if (ret < 0)
		return ret;
	ret = mlx90632_read_ee_register(data->regmap, MLX90632_EE_Eb, &Eb);
	if (ret < 0)
		return ret;
	ret = mlx90632_read_ee_register(data->regmap, MLX90632_EE_Fa, &Fa);
	if (ret < 0)
		return ret;
	ret = mlx90632_read_ee_register(data->regmap, MLX90632_EE_Fb, &Fb);
	if (ret < 0)
		return ret;
	ret = mlx90632_read_ee_register(data->regmap, MLX90632_EE_Ga, &Ga);
	if (ret < 0)
		return ret;
	ret = regmap_read(data->regmap, MLX90632_EE_Ha, &read_tmp);
	if (ret < 0)
		return ret;
	Ha = (s16)read_tmp;
	ret = regmap_read(data->regmap, MLX90632_EE_Hb, &read_tmp);
	if (ret < 0)
		return ret;
	Hb = (s16)read_tmp;
	ret = regmap_read(data->regmap, MLX90632_EE_Gb, &read_tmp);
	if (ret < 0)
		return ret;
	Gb = (s16)read_tmp;
	ret = regmap_read(data->regmap, MLX90632_EE_Ka, &read_tmp);
	if (ret < 0)
		return ret;
	Ka = (s16)read_tmp;

	ret = mlx90632_read_all_channel(data,
					&ambient_new_raw, &ambient_old_raw,
					&object_new_raw, &object_old_raw);
	if (ret < 0)
		return ret;

	ambient = mlx90632_preprocess_temp_amb(ambient_new_raw,
					       ambient_old_raw, Gb);
	object = mlx90632_preprocess_temp_obj(object_new_raw,
					      object_old_raw,
					      ambient_new_raw,
					      ambient_old_raw, Ka);

	*val = mlx90632_calc_temp_object(object, ambient, Ea, Eb, Fa, Fb, Ga,
					 Ha, Hb, data->emissivity);
	return 0;
}