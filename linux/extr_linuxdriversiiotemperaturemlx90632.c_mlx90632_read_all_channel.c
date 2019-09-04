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
struct mlx90632_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 scalar_t__ mlx90632_perform_measurement (struct mlx90632_data*) ; 
 scalar_t__ mlx90632_read_ambient_raw (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mlx90632_read_object_raw (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx90632_read_all_channel(struct mlx90632_data *data,
				     s16 *ambient_new_raw, s16 *ambient_old_raw,
				     s16 *object_new_raw, s16 *object_old_raw)
{
	s32 ret, measurement;

	mutex_lock(&data->lock);
	measurement = mlx90632_perform_measurement(data);
	if (measurement < 0) {
		ret = measurement;
		goto read_unlock;
	}
	ret = mlx90632_read_ambient_raw(data->regmap, ambient_new_raw,
					ambient_old_raw);
	if (ret < 0)
		goto read_unlock;

	ret = mlx90632_read_object_raw(data->regmap, measurement,
				       object_new_raw, object_old_raw);
read_unlock:
	mutex_unlock(&data->lock);
	return ret;
}