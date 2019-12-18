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
struct mlx5e_xdpsq {int /*<<< orphan*/  xmit_xdp_frame; int /*<<< orphan*/  xmit_xdp_frame_check; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_xmit_xdp_frame ; 
 int /*<<< orphan*/  mlx5e_xmit_xdp_frame_check ; 
 int /*<<< orphan*/  mlx5e_xmit_xdp_frame_check_mpwqe ; 
 int /*<<< orphan*/  mlx5e_xmit_xdp_frame_mpwqe ; 

void mlx5e_set_xmit_fp(struct mlx5e_xdpsq *sq, bool is_mpw)
{
	sq->xmit_xdp_frame_check = is_mpw ?
		mlx5e_xmit_xdp_frame_check_mpwqe : mlx5e_xmit_xdp_frame_check;
	sq->xmit_xdp_frame = is_mpw ?
		mlx5e_xmit_xdp_frame_mpwqe : mlx5e_xmit_xdp_frame;
}