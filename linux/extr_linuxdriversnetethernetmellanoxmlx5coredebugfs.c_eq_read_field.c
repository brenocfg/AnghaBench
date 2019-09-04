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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_eq {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
#define  EQ_INTR 130 
#define  EQ_LOG_PG_SZ 129 
#define  EQ_NUM_EQES 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_GET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eq_context_entry ; 
 int /*<<< orphan*/  eqc ; 
 int /*<<< orphan*/  intr ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_eq_size ; 
 int /*<<< orphan*/  log_page_size ; 
 int mlx5_core_eq_query (struct mlx5_core_dev*,struct mlx5_eq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  query_eq_out ; 

__attribute__((used)) static u64 eq_read_field(struct mlx5_core_dev *dev, struct mlx5_eq *eq,
			 int index)
{
	int outlen = MLX5_ST_SZ_BYTES(query_eq_out);
	u64 param = 0;
	void *ctx;
	u32 *out;
	int err;

	out = kzalloc(outlen, GFP_KERNEL);
	if (!out)
		return param;

	err = mlx5_core_eq_query(dev, eq, out, outlen);
	if (err) {
		mlx5_core_warn(dev, "failed to query eq\n");
		goto out;
	}
	ctx = MLX5_ADDR_OF(query_eq_out, out, eq_context_entry);

	switch (index) {
	case EQ_NUM_EQES:
		param = 1 << MLX5_GET(eqc, ctx, log_eq_size);
		break;
	case EQ_INTR:
		param = MLX5_GET(eqc, ctx, intr);
		break;
	case EQ_LOG_PG_SZ:
		param = MLX5_GET(eqc, ctx, log_page_size) + 12;
		break;
	}

out:
	kfree(out);
	return param;
}