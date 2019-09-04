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
typedef  int u8 ;
struct mlx5e_rx_wqe_ll {int dummy; } ;
struct mlx5e_rx_wqe_cyc {int dummy; } ;
struct mlx5_wqe_data_seg {int dummy; } ;

/* Variables and functions */
#define  MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ 128 
 int order_base_2 (int) ; 

__attribute__((used)) static inline u8 mlx5e_get_rqwq_log_stride(u8 wq_type, int ndsegs)
{
	int sz = sizeof(struct mlx5_wqe_data_seg) * ndsegs;

	switch (wq_type) {
	case MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ:
		sz += sizeof(struct mlx5e_rx_wqe_ll);
		break;
	default: /* MLX5_WQ_TYPE_CYCLIC */
		sz += sizeof(struct mlx5e_rx_wqe_cyc);
	}

	return order_base_2(sz);
}