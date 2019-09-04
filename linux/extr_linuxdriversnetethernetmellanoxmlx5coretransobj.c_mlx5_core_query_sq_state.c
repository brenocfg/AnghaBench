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
 int mlx5_core_query_sq (struct mlx5_core_dev*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  query_sq_out ; 
 int /*<<< orphan*/  sq_context ; 

int mlx5_core_query_sq_state(struct mlx5_core_dev *dev, u32 sqn, u8 *state)
{
	void *out;
	void *sqc;
	int inlen;
	int err;

	inlen = MLX5_ST_SZ_BYTES(query_sq_out);
	out = kvzalloc(inlen, GFP_KERNEL);
	if (!out)
		return -ENOMEM;

	err = mlx5_core_query_sq(dev, sqn, out);
	if (err)
		goto out;

	sqc = MLX5_ADDR_OF(query_sq_out, out, sq_context);
	*state = MLX5_GET(sqc, sqc, state);

out:
	kvfree(out);
	return err;
}