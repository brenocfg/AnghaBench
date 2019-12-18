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
typedef  enum mlx5e_traffic_types { ____Placeholder_mlx5e_traffic_types } mlx5e_traffic_types ;
typedef  enum arfs_type { ____Placeholder_arfs_type } arfs_type ;

/* Variables and functions */
#define  ARFS_IPV4_TCP 131 
#define  ARFS_IPV4_UDP 130 
#define  ARFS_IPV6_TCP 129 
#define  ARFS_IPV6_UDP 128 
 int EINVAL ; 
 int MLX5E_TT_IPV4_TCP ; 
 int MLX5E_TT_IPV4_UDP ; 
 int MLX5E_TT_IPV6_TCP ; 
 int MLX5E_TT_IPV6_UDP ; 

__attribute__((used)) static enum mlx5e_traffic_types arfs_get_tt(enum arfs_type type)
{
	switch (type) {
	case ARFS_IPV4_TCP:
		return MLX5E_TT_IPV4_TCP;
	case ARFS_IPV4_UDP:
		return MLX5E_TT_IPV4_UDP;
	case ARFS_IPV6_TCP:
		return MLX5E_TT_IPV6_TCP;
	case ARFS_IPV6_UDP:
		return MLX5E_TT_IPV6_UDP;
	default:
		return -EINVAL;
	}
}