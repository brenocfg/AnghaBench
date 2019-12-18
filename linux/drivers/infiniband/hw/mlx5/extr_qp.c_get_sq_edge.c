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
struct mlx5_ib_wq {int /*<<< orphan*/  fbc; } ;

/* Variables and functions */
 int MLX5_SEND_WQE_BB ; 
 int /*<<< orphan*/  mlx5_frag_buf_get_idx_last_contig_stride (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* mlx5_frag_buf_get_wqe (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *get_sq_edge(struct mlx5_ib_wq *sq, u32 idx)
{
	void *fragment_end;

	fragment_end = mlx5_frag_buf_get_wqe
		(&sq->fbc,
		 mlx5_frag_buf_get_idx_last_contig_stride(&sq->fbc, idx));

	return fragment_end + MLX5_SEND_WQE_BB;
}