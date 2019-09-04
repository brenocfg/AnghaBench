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
struct mlx4_wqe_raddr_seg {int dummy; } ;
struct mlx4_wqe_masked_atomic_seg {int dummy; } ;
struct mlx4_wqe_inline_seg {int dummy; } ;
struct mlx4_wqe_datagram_seg {int dummy; } ;
struct mlx4_wqe_data_seg {int dummy; } ;
struct mlx4_wqe_ctrl_seg {int dummy; } ;
typedef  enum mlx4_ib_qp_type { ____Placeholder_mlx4_ib_qp_type } mlx4_ib_qp_type ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX4_IB_LSO_HEADER_SPARE ; 
#define  MLX4_IB_QPT_GSI 137 
#define  MLX4_IB_QPT_PROXY_GSI 136 
#define  MLX4_IB_QPT_PROXY_SMI 135 
#define  MLX4_IB_QPT_PROXY_SMI_OWNER 134 
#define  MLX4_IB_QPT_RC 133 
#define  MLX4_IB_QPT_SMI 132 
#define  MLX4_IB_QPT_TUN_GSI 131 
#define  MLX4_IB_QPT_TUN_SMI_OWNER 130 
#define  MLX4_IB_QPT_UC 129 
#define  MLX4_IB_QPT_UD 128 
 int MLX4_IB_QP_LSO ; 
 int /*<<< orphan*/  MLX4_IB_UD_HEADER_SIZE ; 
 int /*<<< orphan*/  MLX4_INLINE_ALIGN ; 

__attribute__((used)) static int send_wqe_overhead(enum mlx4_ib_qp_type type, u32 flags)
{
	/*
	 * UD WQEs must have a datagram segment.
	 * RC and UC WQEs might have a remote address segment.
	 * MLX WQEs need two extra inline data segments (for the UD
	 * header and space for the ICRC).
	 */
	switch (type) {
	case MLX4_IB_QPT_UD:
		return sizeof (struct mlx4_wqe_ctrl_seg) +
			sizeof (struct mlx4_wqe_datagram_seg) +
			((flags & MLX4_IB_QP_LSO) ? MLX4_IB_LSO_HEADER_SPARE : 0);
	case MLX4_IB_QPT_PROXY_SMI_OWNER:
	case MLX4_IB_QPT_PROXY_SMI:
	case MLX4_IB_QPT_PROXY_GSI:
		return sizeof (struct mlx4_wqe_ctrl_seg) +
			sizeof (struct mlx4_wqe_datagram_seg) + 64;
	case MLX4_IB_QPT_TUN_SMI_OWNER:
	case MLX4_IB_QPT_TUN_GSI:
		return sizeof (struct mlx4_wqe_ctrl_seg) +
			sizeof (struct mlx4_wqe_datagram_seg);

	case MLX4_IB_QPT_UC:
		return sizeof (struct mlx4_wqe_ctrl_seg) +
			sizeof (struct mlx4_wqe_raddr_seg);
	case MLX4_IB_QPT_RC:
		return sizeof (struct mlx4_wqe_ctrl_seg) +
			sizeof (struct mlx4_wqe_masked_atomic_seg) +
			sizeof (struct mlx4_wqe_raddr_seg);
	case MLX4_IB_QPT_SMI:
	case MLX4_IB_QPT_GSI:
		return sizeof (struct mlx4_wqe_ctrl_seg) +
			ALIGN(MLX4_IB_UD_HEADER_SIZE +
			      DIV_ROUND_UP(MLX4_IB_UD_HEADER_SIZE,
					   MLX4_INLINE_ALIGN) *
			      sizeof (struct mlx4_wqe_inline_seg),
			      sizeof (struct mlx4_wqe_data_seg)) +
			ALIGN(4 +
			      sizeof (struct mlx4_wqe_inline_seg),
			      sizeof (struct mlx4_wqe_data_seg));
	default:
		return sizeof (struct mlx4_wqe_ctrl_seg);
	}
}