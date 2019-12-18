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
struct mlx5_fc {int /*<<< orphan*/  id; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlx5_fc* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mlx5_fc*) ; 
 struct mlx5_fc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_cmd_fc_alloc (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlx5_fc *mlx5_fc_single_alloc(struct mlx5_core_dev *dev)
{
	struct mlx5_fc *counter;
	int err;

	counter = kzalloc(sizeof(*counter), GFP_KERNEL);
	if (!counter)
		return ERR_PTR(-ENOMEM);

	err = mlx5_cmd_fc_alloc(dev, &counter->id);
	if (err) {
		kfree(counter);
		return ERR_PTR(err);
	}

	return counter;
}