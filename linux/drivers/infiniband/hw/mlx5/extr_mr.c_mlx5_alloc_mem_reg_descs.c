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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_mtt {int dummy; } ;
struct mlx5_ib_mr {int dummy; } ;
struct ib_pd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_MKC_ACCESS_MODE_MTT ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int _mlx5_alloc_mkey_descs (struct ib_pd*,struct mlx5_ib_mr*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mlx5_alloc_mem_reg_descs(struct ib_pd *pd, struct mlx5_ib_mr *mr,
				    int ndescs, u32 *in, int inlen)
{
	return _mlx5_alloc_mkey_descs(pd, mr, ndescs, sizeof(struct mlx5_mtt),
				      PAGE_SHIFT, MLX5_MKC_ACCESS_MODE_MTT, in,
				      inlen);
}