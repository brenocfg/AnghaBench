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
struct mlx5_core_dev {int dummy; } ;
struct mlx5_core_cq {int pid; } ;

/* Variables and functions */
#define  CQ_LOG_PG_SZ 130 
#define  CQ_NUM_CQES 129 
#define  CQ_PID 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_GET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cq_context ; 
 int /*<<< orphan*/  cqc ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_cq_size ; 
 int /*<<< orphan*/  log_page_size ; 
 int mlx5_core_query_cq (struct mlx5_core_dev*,struct mlx5_core_cq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  query_cq_out ; 

__attribute__((used)) static u64 cq_read_field(struct mlx5_core_dev *dev, struct mlx5_core_cq *cq,
			 int index)
{
	int outlen = MLX5_ST_SZ_BYTES(query_cq_out);
	u64 param = 0;
	void *ctx;
	u32 *out;
	int err;

	out = kvzalloc(outlen, GFP_KERNEL);
	if (!out)
		return param;

	err = mlx5_core_query_cq(dev, cq, out, outlen);
	if (err) {
		mlx5_core_warn(dev, "failed to query cq\n");
		goto out;
	}
	ctx = MLX5_ADDR_OF(query_cq_out, out, cq_context);

	switch (index) {
	case CQ_PID:
		param = cq->pid;
		break;
	case CQ_NUM_CQES:
		param = 1 << MLX5_GET(cqc, ctx, log_cq_size);
		break;
	case CQ_LOG_PG_SZ:
		param = MLX5_GET(cqc, ctx, log_page_size);
		break;
	}

out:
	kvfree(out);
	return param;
}