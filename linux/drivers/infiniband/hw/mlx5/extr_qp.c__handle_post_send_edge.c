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
typedef  int u32 ;
struct mlx5_ib_wq {int cur_post; int wqe_cnt; int /*<<< orphan*/  fbc; } ;

/* Variables and functions */
 void* get_sq_edge (struct mlx5_ib_wq*,int) ; 
 void* mlx5_frag_buf_get_wqe (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void _handle_post_send_edge(struct mlx5_ib_wq *sq, void **seg,
				   u32 wqe_sz, void **cur_edge)
{
	u32 idx;

	idx = (sq->cur_post + (wqe_sz >> 2)) & (sq->wqe_cnt - 1);
	*cur_edge = get_sq_edge(sq, idx);

	*seg = mlx5_frag_buf_get_wqe(&sq->fbc, idx);
}