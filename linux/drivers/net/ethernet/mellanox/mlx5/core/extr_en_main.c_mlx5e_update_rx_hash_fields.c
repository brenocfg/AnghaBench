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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5e_tirc_config {int /*<<< orphan*/  rx_hash_fields; } ;
typedef  enum mlx5e_traffic_types { ____Placeholder_mlx5e_traffic_types } mlx5e_traffic_types ;

/* Variables and functions */
 struct mlx5e_tirc_config* tirc_default_config ; 

__attribute__((used)) static void mlx5e_update_rx_hash_fields(struct mlx5e_tirc_config *ttconfig,
					enum mlx5e_traffic_types tt,
					u32 rx_hash_fields)
{
	*ttconfig                = tirc_default_config[tt];
	ttconfig->rx_hash_fields = rx_hash_fields;
}