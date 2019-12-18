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
typedef  int /*<<< orphan*/  u64 ;
struct mlx5_lag {TYPE_1__* pf; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_2__ {struct mlx5_core_dev* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5_MAX_PORTS ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 scalar_t__ __mlx5_lag_is_roce (struct mlx5_lag*) ; 
 scalar_t__ be64_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lag_mutex ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mlx5_cmd_query_cong_counter (struct mlx5_core_dev*,int,void*,int) ; 
 struct mlx5_lag* mlx5_lag_dev_get (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  query_cong_statistics_out ; 

int mlx5_lag_query_cong_counters(struct mlx5_core_dev *dev,
				 u64 *values,
				 int num_counters,
				 size_t *offsets)
{
	int outlen = MLX5_ST_SZ_BYTES(query_cong_statistics_out);
	struct mlx5_core_dev *mdev[MLX5_MAX_PORTS];
	struct mlx5_lag *ldev;
	int num_ports;
	int ret, i, j;
	void *out;

	out = kvzalloc(outlen, GFP_KERNEL);
	if (!out)
		return -ENOMEM;

	memset(values, 0, sizeof(*values) * num_counters);

	mutex_lock(&lag_mutex);
	ldev = mlx5_lag_dev_get(dev);
	if (ldev && __mlx5_lag_is_roce(ldev)) {
		num_ports = MLX5_MAX_PORTS;
		mdev[0] = ldev->pf[0].dev;
		mdev[1] = ldev->pf[1].dev;
	} else {
		num_ports = 1;
		mdev[0] = dev;
	}

	for (i = 0; i < num_ports; ++i) {
		ret = mlx5_cmd_query_cong_counter(mdev[i], false, out, outlen);
		if (ret)
			goto unlock;

		for (j = 0; j < num_counters; ++j)
			values[j] += be64_to_cpup((__be64 *)(out + offsets[j]));
	}

unlock:
	mutex_unlock(&lag_mutex);
	kvfree(out);
	return ret;
}