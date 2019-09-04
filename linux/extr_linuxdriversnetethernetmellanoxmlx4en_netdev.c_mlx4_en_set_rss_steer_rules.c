#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct mlx4_mac_entry {size_t* mac; int /*<<< orphan*/  hlist; int /*<<< orphan*/  reg_id; } ;
struct mlx4_en_priv {int base_qpn; size_t* current_mac; TYPE_2__* dev; int /*<<< orphan*/  tunnel_reg_id; TYPE_1__* mdev; int /*<<< orphan*/ * mac_hash; } ;
struct TYPE_4__ {size_t* dev_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t MLX4_EN_MAC_HASH_IDX ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mlx4_mac_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,int) ; 
 int mlx4_en_tunnel_steer_add (struct mlx4_en_priv*,size_t*,int,int /*<<< orphan*/ *) ; 
 int mlx4_en_uc_steer_add (struct mlx4_en_priv*,size_t*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_en_uc_steer_release (struct mlx4_en_priv*,size_t*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_flow_detach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_en_set_rss_steer_rules(struct mlx4_en_priv *priv)
{
	u64 reg_id;
	int err = 0;
	int *qpn = &priv->base_qpn;
	struct mlx4_mac_entry *entry;

	err = mlx4_en_uc_steer_add(priv, priv->dev->dev_addr, qpn, &reg_id);
	if (err)
		return err;

	err = mlx4_en_tunnel_steer_add(priv, priv->dev->dev_addr, *qpn,
				       &priv->tunnel_reg_id);
	if (err)
		goto tunnel_err;

	entry = kmalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry) {
		err = -ENOMEM;
		goto alloc_err;
	}

	memcpy(entry->mac, priv->dev->dev_addr, sizeof(entry->mac));
	memcpy(priv->current_mac, entry->mac, sizeof(priv->current_mac));
	entry->reg_id = reg_id;
	hlist_add_head_rcu(&entry->hlist,
			   &priv->mac_hash[entry->mac[MLX4_EN_MAC_HASH_IDX]]);

	return 0;

alloc_err:
	if (priv->tunnel_reg_id)
		mlx4_flow_detach(priv->mdev->dev, priv->tunnel_reg_id);

tunnel_err:
	mlx4_en_uc_steer_release(priv, priv->dev->dev_addr, *qpn, reg_id);
	return err;
}