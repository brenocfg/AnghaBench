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
typedef  enum mlx4_resource { ____Placeholder_mlx4_resource } mlx4_resource ;

/* Variables and functions */
#define  RES_COUNTER 138 
#define  RES_CQ 137 
#define  RES_EQ 136 
#define  RES_FS_RULE 135 
#define  RES_MAC 134 
#define  RES_MPT 133 
#define  RES_MTT 132 
#define  RES_QP 131 
#define  RES_SRQ 130 
#define  RES_VLAN 129 
#define  RES_XRCD 128 

__attribute__((used)) static const char *mlx4_resource_type_to_str(enum mlx4_resource t)
{
	switch (t) {
	case RES_QP:
		return "QP";
	case RES_CQ:
		return "CQ";
	case RES_SRQ:
		return "SRQ";
	case RES_XRCD:
		return "XRCD";
	case RES_MPT:
		return "MPT";
	case RES_MTT:
		return "MTT";
	case RES_MAC:
		return "MAC";
	case RES_VLAN:
		return "VLAN";
	case RES_COUNTER:
		return "COUNTER";
	case RES_FS_RULE:
		return "FS_RULE";
	case RES_EQ:
		return "EQ";
	default:
		return "INVALID RESOURCE";
	}
}