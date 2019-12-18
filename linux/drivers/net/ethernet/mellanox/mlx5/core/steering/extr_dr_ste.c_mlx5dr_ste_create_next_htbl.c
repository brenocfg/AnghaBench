#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx5dr_ste_htbl {struct mlx5dr_ste* pointing_ste; } ;
struct mlx5dr_ste {struct mlx5dr_ste_htbl* next_htbl; int /*<<< orphan*/  ste_chain_location; } ;
struct mlx5dr_matcher_rx_tx {TYPE_4__* e_anchor; TYPE_1__* nic_tbl; } ;
struct mlx5dr_matcher {TYPE_2__* tbl; } ;
struct mlx5dr_htbl_connect_info {int /*<<< orphan*/  miss_icm_addr; int /*<<< orphan*/  type; } ;
struct mlx5dr_domain_rx_tx {int dummy; } ;
struct mlx5dr_domain {int /*<<< orphan*/  ste_icm_pool; } ;
struct dr_hw_ste_format {int dummy; } ;
typedef  enum mlx5dr_icm_chunk_size { ____Placeholder_mlx5dr_icm_chunk_size } mlx5dr_icm_chunk_size ;
struct TYPE_8__ {TYPE_3__* chunk; } ;
struct TYPE_7__ {int /*<<< orphan*/  icm_addr; } ;
struct TYPE_6__ {struct mlx5dr_domain* dmn; } ;
struct TYPE_5__ {struct mlx5dr_domain_rx_tx* nic_dmn; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int /*<<< orphan*/  CONNECT_MISS ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ ,struct dr_hw_ste_format*,int /*<<< orphan*/ ) ; 
 int get_bits_per_mask (int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mlx5dr_dbg (struct mlx5dr_domain*,char*) ; 
 int /*<<< orphan*/  mlx5dr_info (struct mlx5dr_domain*,char*) ; 
 struct mlx5dr_ste_htbl* mlx5dr_ste_htbl_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_ste_htbl_free (struct mlx5dr_ste_htbl*) ; 
 scalar_t__ mlx5dr_ste_htbl_init_and_postsend (struct mlx5dr_domain*,struct mlx5dr_domain_rx_tx*,struct mlx5dr_ste_htbl*,struct mlx5dr_htbl_connect_info*,int) ; 
 int /*<<< orphan*/  mlx5dr_ste_is_last_in_rule (struct mlx5dr_matcher_rx_tx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_ste_set_hit_addr_by_next_htbl (int /*<<< orphan*/ *,struct mlx5dr_ste_htbl*) ; 
 int /*<<< orphan*/  ste_general ; 

int mlx5dr_ste_create_next_htbl(struct mlx5dr_matcher *matcher,
				struct mlx5dr_matcher_rx_tx *nic_matcher,
				struct mlx5dr_ste *ste,
				u8 *cur_hw_ste,
				enum mlx5dr_icm_chunk_size log_table_size)
{
	struct dr_hw_ste_format *hw_ste = (struct dr_hw_ste_format *)cur_hw_ste;
	struct mlx5dr_domain_rx_tx *nic_dmn = nic_matcher->nic_tbl->nic_dmn;
	struct mlx5dr_domain *dmn = matcher->tbl->dmn;
	struct mlx5dr_htbl_connect_info info;
	struct mlx5dr_ste_htbl *next_htbl;

	if (!mlx5dr_ste_is_last_in_rule(nic_matcher, ste->ste_chain_location)) {
		u32 bits_in_mask;
		u8 next_lu_type;
		u16 byte_mask;

		next_lu_type = MLX5_GET(ste_general, hw_ste, next_lu_type);
		byte_mask = MLX5_GET(ste_general, hw_ste, byte_mask);

		/* Don't allocate table more than required,
		 * the size of the table defined via the byte_mask, so no need
		 * to allocate more than that.
		 */
		bits_in_mask = get_bits_per_mask(byte_mask) * BITS_PER_BYTE;
		log_table_size = min(log_table_size, bits_in_mask);

		next_htbl = mlx5dr_ste_htbl_alloc(dmn->ste_icm_pool,
						  log_table_size,
						  next_lu_type,
						  byte_mask);
		if (!next_htbl) {
			mlx5dr_dbg(dmn, "Failed allocating table\n");
			return -ENOMEM;
		}

		/* Write new table to HW */
		info.type = CONNECT_MISS;
		info.miss_icm_addr = nic_matcher->e_anchor->chunk->icm_addr;
		if (mlx5dr_ste_htbl_init_and_postsend(dmn, nic_dmn, next_htbl,
						      &info, false)) {
			mlx5dr_info(dmn, "Failed writing table to HW\n");
			goto free_table;
		}

		mlx5dr_ste_set_hit_addr_by_next_htbl(cur_hw_ste, next_htbl);
		ste->next_htbl = next_htbl;
		next_htbl->pointing_ste = ste;
	}

	return 0;

free_table:
	mlx5dr_ste_htbl_free(next_htbl);
	return -ENOENT;
}