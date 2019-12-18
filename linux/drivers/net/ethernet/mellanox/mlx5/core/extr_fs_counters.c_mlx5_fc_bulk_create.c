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
typedef  scalar_t__ u32 ;
struct mlx5_fc_bulk {int bulk_len; struct mlx5_fc_bulk* bitmask; int /*<<< orphan*/ * fcs; scalar_t__ base_id; } ;
struct mlx5_fc {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  enum mlx5_fc_bulk_alloc_bitmask { ____Placeholder_mlx5_fc_bulk_alloc_bitmask } mlx5_fc_bulk_alloc_bitmask ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_LONGS (int) ; 
 int ENOMEM ; 
 struct mlx5_fc_bulk* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int MLX5_FC_BULK_NUM_FCS (int) ; 
 int /*<<< orphan*/  flow_counter_bulk_alloc ; 
 struct mlx5_fc_bulk* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_fc_bulk*) ; 
 struct mlx5_fc_bulk* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_cmd_fc_bulk_alloc (struct mlx5_core_dev*,int,scalar_t__*) ; 
 int /*<<< orphan*/  mlx5_fc_init (int /*<<< orphan*/ *,struct mlx5_fc_bulk*,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int,struct mlx5_fc_bulk*) ; 

__attribute__((used)) static struct mlx5_fc_bulk *mlx5_fc_bulk_create(struct mlx5_core_dev *dev)
{
	enum mlx5_fc_bulk_alloc_bitmask alloc_bitmask;
	struct mlx5_fc_bulk *bulk;
	int err = -ENOMEM;
	int bulk_len;
	u32 base_id;
	int i;

	alloc_bitmask = MLX5_CAP_GEN(dev, flow_counter_bulk_alloc);
	bulk_len = alloc_bitmask > 0 ? MLX5_FC_BULK_NUM_FCS(alloc_bitmask) : 1;

	bulk = kzalloc(sizeof(*bulk) + bulk_len * sizeof(struct mlx5_fc),
		       GFP_KERNEL);
	if (!bulk)
		goto err_alloc_bulk;

	bulk->bitmask = kcalloc(BITS_TO_LONGS(bulk_len), sizeof(unsigned long),
				GFP_KERNEL);
	if (!bulk->bitmask)
		goto err_alloc_bitmask;

	err = mlx5_cmd_fc_bulk_alloc(dev, alloc_bitmask, &base_id);
	if (err)
		goto err_mlx5_cmd_bulk_alloc;

	bulk->base_id = base_id;
	bulk->bulk_len = bulk_len;
	for (i = 0; i < bulk_len; i++) {
		mlx5_fc_init(&bulk->fcs[i], bulk, base_id + i);
		set_bit(i, bulk->bitmask);
	}

	return bulk;

err_mlx5_cmd_bulk_alloc:
	kfree(bulk->bitmask);
err_alloc_bitmask:
	kfree(bulk);
err_alloc_bulk:
	return ERR_PTR(err);
}