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
struct mlx5e_tirc_config {int dummy; } ;
typedef  enum mlx5e_traffic_types { ____Placeholder_mlx5e_traffic_types } mlx5e_traffic_types ;

/* Variables and functions */
 struct mlx5e_tirc_config* tirc_default_config ; 

struct mlx5e_tirc_config mlx5e_tirc_get_default_config(enum mlx5e_traffic_types tt)
{
	return tirc_default_config[tt];
}