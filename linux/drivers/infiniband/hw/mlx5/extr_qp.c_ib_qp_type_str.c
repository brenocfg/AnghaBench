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
#define  IB_QPT_DRIVER 140 
#define  IB_QPT_GSI 139 
#define  IB_QPT_MAX 138 
#define  IB_QPT_RAW_ETHERTYPE 137 
#define  IB_QPT_RAW_IPV6 136 
#define  IB_QPT_RAW_PACKET 135 
#define  IB_QPT_RC 134 
#define  IB_QPT_SMI 133 
#define  IB_QPT_UC 132 
#define  IB_QPT_UD 131 
#define  IB_QPT_XRC_INI 130 
#define  IB_QPT_XRC_TGT 129 
#define  MLX5_IB_QPT_REG_UMR 128 

__attribute__((used)) static const char *ib_qp_type_str(enum ib_qp_type type)
{
	switch (type) {
	case IB_QPT_SMI:
		return "IB_QPT_SMI";
	case IB_QPT_GSI:
		return "IB_QPT_GSI";
	case IB_QPT_RC:
		return "IB_QPT_RC";
	case IB_QPT_UC:
		return "IB_QPT_UC";
	case IB_QPT_UD:
		return "IB_QPT_UD";
	case IB_QPT_RAW_IPV6:
		return "IB_QPT_RAW_IPV6";
	case IB_QPT_RAW_ETHERTYPE:
		return "IB_QPT_RAW_ETHERTYPE";
	case IB_QPT_XRC_INI:
		return "IB_QPT_XRC_INI";
	case IB_QPT_XRC_TGT:
		return "IB_QPT_XRC_TGT";
	case IB_QPT_RAW_PACKET:
		return "IB_QPT_RAW_PACKET";
	case MLX5_IB_QPT_REG_UMR:
		return "MLX5_IB_QPT_REG_UMR";
	case IB_QPT_DRIVER:
		return "IB_QPT_DRIVER";
	case IB_QPT_MAX:
	default:
		return "Invalid QP type";
	}
}