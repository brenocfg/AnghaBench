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
struct mlx5_geneve {int /*<<< orphan*/  obj_id; int /*<<< orphan*/  mdev; scalar_t__ refcount; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct mlx5_geneve*) ; 
 int /*<<< orphan*/  kfree (struct mlx5_geneve*) ; 
 int /*<<< orphan*/  mlx5_geneve_tlv_option_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mlx5_geneve_destroy(struct mlx5_geneve *geneve)
{
	if (IS_ERR_OR_NULL(geneve))
		return;

	/* Lockless since we are unloading */
	if (geneve->refcount)
		mlx5_geneve_tlv_option_destroy(geneve->mdev, geneve->obj_id);

	kfree(geneve);
}