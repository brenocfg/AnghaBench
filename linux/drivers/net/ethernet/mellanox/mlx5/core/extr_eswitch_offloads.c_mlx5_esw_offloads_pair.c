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
struct mlx5_eswitch {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int esw_add_fdb_peer_miss_rules (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5_esw_offloads_pair(struct mlx5_eswitch *esw,
				  struct mlx5_eswitch *peer_esw)
{
	int err;

	err = esw_add_fdb_peer_miss_rules(esw, peer_esw->dev);
	if (err)
		return err;

	return 0;
}