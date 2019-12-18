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
struct mlx5_geneve {int /*<<< orphan*/  sync_lock; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mlx5_geneve* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mlx5_geneve* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct mlx5_geneve *mlx5_geneve_create(struct mlx5_core_dev *mdev)
{
	struct mlx5_geneve *geneve =
		kzalloc(sizeof(*geneve), GFP_KERNEL);

	if (!geneve)
		return ERR_PTR(-ENOMEM);
	geneve->mdev = mdev;
	mutex_init(&geneve->sync_lock);

	return geneve;
}