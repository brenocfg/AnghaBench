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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_GET (void*,void*,int /*<<< orphan*/ *) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_core_query_rq (struct mlx5_core_dev*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  query_rq_out ; 
 int /*<<< orphan*/  rq_context ; 

__attribute__((used)) static int mlx5e_query_rq_state(struct mlx5_core_dev *dev, u32 rqn, u8 *state)
{
	int outlen = MLX5_ST_SZ_BYTES(query_rq_out);
	void *out;
	void *rqc;
	int err;

	out = kvzalloc(outlen, GFP_KERNEL);
	if (!out)
		return -ENOMEM;

	err = mlx5_core_query_rq(dev, rqn, out);
	if (err)
		goto out;

	rqc = MLX5_ADDR_OF(query_rq_out, out, rq_context);
	*state = MLX5_GET(rqc, rqc, state);

out:
	kvfree(out);
	return err;
}