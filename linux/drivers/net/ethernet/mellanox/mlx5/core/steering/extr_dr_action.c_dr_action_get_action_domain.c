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
typedef  enum mlx5dr_ste_entry_type { ____Placeholder_mlx5dr_ste_entry_type } mlx5dr_ste_entry_type ;
typedef  enum mlx5dr_domain_type { ____Placeholder_mlx5dr_domain_type } mlx5dr_domain_type ;
typedef  enum dr_action_domain { ____Placeholder_dr_action_domain } dr_action_domain ;

/* Variables and functions */
 int DR_ACTION_DOMAIN_FDB_EGRESS ; 
 int DR_ACTION_DOMAIN_FDB_INGRESS ; 
 int DR_ACTION_DOMAIN_MAX ; 
 int DR_ACTION_DOMAIN_NIC_EGRESS ; 
 int DR_ACTION_DOMAIN_NIC_INGRESS ; 
#define  MLX5DR_DOMAIN_TYPE_FDB 130 
#define  MLX5DR_DOMAIN_TYPE_NIC_RX 129 
#define  MLX5DR_DOMAIN_TYPE_NIC_TX 128 
 int MLX5DR_STE_TYPE_RX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static enum dr_action_domain
dr_action_get_action_domain(enum mlx5dr_domain_type domain,
			    enum mlx5dr_ste_entry_type ste_type)
{
	switch (domain) {
	case MLX5DR_DOMAIN_TYPE_NIC_RX:
		return DR_ACTION_DOMAIN_NIC_INGRESS;
	case MLX5DR_DOMAIN_TYPE_NIC_TX:
		return DR_ACTION_DOMAIN_NIC_EGRESS;
	case MLX5DR_DOMAIN_TYPE_FDB:
		if (ste_type == MLX5DR_STE_TYPE_RX)
			return DR_ACTION_DOMAIN_FDB_INGRESS;
		return DR_ACTION_DOMAIN_FDB_EGRESS;
	default:
		WARN_ON(true);
		return DR_ACTION_DOMAIN_MAX;
	}
}