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
typedef  enum mlx5e_traffic_types { ____Placeholder_mlx5e_traffic_types } mlx5e_traffic_types ;

/* Variables and functions */
#define  AH_V4_FLOW 137 
#define  AH_V6_FLOW 136 
#define  ESP_V4_FLOW 135 
#define  ESP_V6_FLOW 134 
#define  IPV4_FLOW 133 
#define  IPV6_FLOW 132 
 int MLX5E_NUM_INDIR_TIRS ; 
 int MLX5E_TT_IPV4 ; 
 int MLX5E_TT_IPV4_IPSEC_AH ; 
 int MLX5E_TT_IPV4_IPSEC_ESP ; 
 int MLX5E_TT_IPV4_TCP ; 
 int MLX5E_TT_IPV4_UDP ; 
 int MLX5E_TT_IPV6 ; 
 int MLX5E_TT_IPV6_IPSEC_AH ; 
 int MLX5E_TT_IPV6_IPSEC_ESP ; 
 int MLX5E_TT_IPV6_TCP ; 
 int MLX5E_TT_IPV6_UDP ; 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 

__attribute__((used)) static enum mlx5e_traffic_types flow_type_to_traffic_type(u32 flow_type)
{
	switch (flow_type) {
	case TCP_V4_FLOW:
		return  MLX5E_TT_IPV4_TCP;
	case TCP_V6_FLOW:
		return MLX5E_TT_IPV6_TCP;
	case UDP_V4_FLOW:
		return MLX5E_TT_IPV4_UDP;
	case UDP_V6_FLOW:
		return MLX5E_TT_IPV6_UDP;
	case AH_V4_FLOW:
		return MLX5E_TT_IPV4_IPSEC_AH;
	case AH_V6_FLOW:
		return MLX5E_TT_IPV6_IPSEC_AH;
	case ESP_V4_FLOW:
		return MLX5E_TT_IPV4_IPSEC_ESP;
	case ESP_V6_FLOW:
		return MLX5E_TT_IPV6_IPSEC_ESP;
	case IPV4_FLOW:
		return MLX5E_TT_IPV4;
	case IPV6_FLOW:
		return MLX5E_TT_IPV6;
	default:
		return MLX5E_NUM_INDIR_TIRS;
	}
}