#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct mlx5e_rss_params {int /*<<< orphan*/ * rx_hash_fields; int /*<<< orphan*/  indirection_rqt; int /*<<< orphan*/  toeplitz_hash_key; int /*<<< orphan*/  hfunc; } ;
typedef  enum mlx5e_traffic_types { ____Placeholder_mlx5e_traffic_types } mlx5e_traffic_types ;
struct TYPE_2__ {int /*<<< orphan*/  rx_hash_fields; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_RSS_HASH_TOP ; 
 int /*<<< orphan*/  MLX5E_INDIR_RQT_SIZE ; 
 int MLX5E_NUM_INDIR_TIRS ; 
 int /*<<< orphan*/  mlx5e_build_default_indir_rqt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_rss_key_fill (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* tirc_default_config ; 

void mlx5e_build_rss_params(struct mlx5e_rss_params *rss_params,
			    u16 num_channels)
{
	enum mlx5e_traffic_types tt;

	rss_params->hfunc = ETH_RSS_HASH_TOP;
	netdev_rss_key_fill(rss_params->toeplitz_hash_key,
			    sizeof(rss_params->toeplitz_hash_key));
	mlx5e_build_default_indir_rqt(rss_params->indirection_rqt,
				      MLX5E_INDIR_RQT_SIZE, num_channels);
	for (tt = 0; tt < MLX5E_NUM_INDIR_TIRS; tt++)
		rss_params->rx_hash_fields[tt] =
			tirc_default_config[tt].rx_hash_fields;
}