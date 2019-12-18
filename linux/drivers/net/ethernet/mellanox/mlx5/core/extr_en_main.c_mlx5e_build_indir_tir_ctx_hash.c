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
struct mlx5e_tirc_config {int l3_prot_type; int l4_prot_type; int rx_hash_fields; } ;
struct mlx5e_rss_params {scalar_t__ hfunc; int /*<<< orphan*/  toeplitz_hash_key; } ;

/* Variables and functions */
 scalar_t__ ETH_RSS_HASH_TOP ; 
 void* MLX5_ADDR_OF (void*,void*,int /*<<< orphan*/ ) ; 
 size_t MLX5_FLD_SZ_BYTES (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  l3_prot_type ; 
 int /*<<< orphan*/  l4_prot_type ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 
 int mlx5e_rx_hash_fn (scalar_t__) ; 
 void* rx_hash_field_select ; 
 int /*<<< orphan*/  rx_hash_field_selector_inner ; 
 int /*<<< orphan*/  rx_hash_field_selector_outer ; 
 int /*<<< orphan*/  rx_hash_fn ; 
 int /*<<< orphan*/  rx_hash_symmetric ; 
 int /*<<< orphan*/  rx_hash_toeplitz_key ; 
 int /*<<< orphan*/  selected_fields ; 

void mlx5e_build_indir_tir_ctx_hash(struct mlx5e_rss_params *rss_params,
				    const struct mlx5e_tirc_config *ttconfig,
				    void *tirc, bool inner)
{
	void *hfso = inner ? MLX5_ADDR_OF(tirc, tirc, rx_hash_field_selector_inner) :
			     MLX5_ADDR_OF(tirc, tirc, rx_hash_field_selector_outer);

	MLX5_SET(tirc, tirc, rx_hash_fn, mlx5e_rx_hash_fn(rss_params->hfunc));
	if (rss_params->hfunc == ETH_RSS_HASH_TOP) {
		void *rss_key = MLX5_ADDR_OF(tirc, tirc,
					     rx_hash_toeplitz_key);
		size_t len = MLX5_FLD_SZ_BYTES(tirc,
					       rx_hash_toeplitz_key);

		MLX5_SET(tirc, tirc, rx_hash_symmetric, 1);
		memcpy(rss_key, rss_params->toeplitz_hash_key, len);
	}
	MLX5_SET(rx_hash_field_select, hfso, l3_prot_type,
		 ttconfig->l3_prot_type);
	MLX5_SET(rx_hash_field_select, hfso, l4_prot_type,
		 ttconfig->l4_prot_type);
	MLX5_SET(rx_hash_field_select, hfso, selected_fields,
		 ttconfig->rx_hash_fields);
}