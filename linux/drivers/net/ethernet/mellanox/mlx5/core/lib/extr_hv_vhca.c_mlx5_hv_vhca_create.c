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
struct mlx5_hv_vhca {int /*<<< orphan*/  agents_lock; struct mlx5_core_dev* dev; int /*<<< orphan*/  work_queue; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mlx5_hv_vhca* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  kfree (struct mlx5_hv_vhca*) ; 
 struct mlx5_hv_vhca* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct mlx5_hv_vhca *mlx5_hv_vhca_create(struct mlx5_core_dev *dev)
{
	struct mlx5_hv_vhca *hv_vhca = NULL;

	hv_vhca = kzalloc(sizeof(*hv_vhca), GFP_KERNEL);
	if (!hv_vhca)
		return ERR_PTR(-ENOMEM);

	hv_vhca->work_queue = create_singlethread_workqueue("mlx5_hv_vhca");
	if (!hv_vhca->work_queue) {
		kfree(hv_vhca);
		return ERR_PTR(-ENOMEM);
	}

	hv_vhca->dev = dev;
	mutex_init(&hv_vhca->agents_lock);

	return hv_vhca;
}