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
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;

/* Variables and functions */
 int EINVAL ; 
#define  IB_QPT_MAX 140 
#define  IB_QPT_RAW_ETHERTYPE 139 
#define  IB_QPT_RAW_IPV6 138 
#define  IB_QPT_RAW_PACKET 137 
#define  IB_QPT_RC 136 
#define  IB_QPT_SMI 135 
#define  IB_QPT_UC 134 
#define  IB_QPT_UD 133 
#define  IB_QPT_XRC_INI 132 
#define  IB_QPT_XRC_TGT 131 
#define  MLX5_IB_QPT_DCI 130 
#define  MLX5_IB_QPT_HW_GSI 129 
#define  MLX5_IB_QPT_REG_UMR 128 
 int MLX5_QP_ST_DCI ; 
 int MLX5_QP_ST_QP0 ; 
 int MLX5_QP_ST_QP1 ; 
 int MLX5_QP_ST_RAW_ETHERTYPE ; 
 int MLX5_QP_ST_RAW_IPV6 ; 
 int MLX5_QP_ST_RC ; 
 int MLX5_QP_ST_REG_UMR ; 
 int MLX5_QP_ST_UC ; 
 int MLX5_QP_ST_UD ; 
 int MLX5_QP_ST_XRC ; 

__attribute__((used)) static int to_mlx5_st(enum ib_qp_type type)
{
	switch (type) {
	case IB_QPT_RC:			return MLX5_QP_ST_RC;
	case IB_QPT_UC:			return MLX5_QP_ST_UC;
	case IB_QPT_UD:			return MLX5_QP_ST_UD;
	case MLX5_IB_QPT_REG_UMR:	return MLX5_QP_ST_REG_UMR;
	case IB_QPT_XRC_INI:
	case IB_QPT_XRC_TGT:		return MLX5_QP_ST_XRC;
	case IB_QPT_SMI:		return MLX5_QP_ST_QP0;
	case MLX5_IB_QPT_HW_GSI:	return MLX5_QP_ST_QP1;
	case MLX5_IB_QPT_DCI:		return MLX5_QP_ST_DCI;
	case IB_QPT_RAW_IPV6:		return MLX5_QP_ST_RAW_IPV6;
	case IB_QPT_RAW_PACKET:
	case IB_QPT_RAW_ETHERTYPE:	return MLX5_QP_ST_RAW_ETHERTYPE;
	case IB_QPT_MAX:
	default:		return -EINVAL;
	}
}