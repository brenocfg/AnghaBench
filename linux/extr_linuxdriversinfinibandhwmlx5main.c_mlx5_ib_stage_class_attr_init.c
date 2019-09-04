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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mlx5_ib_dev {TYPE_1__ ib_dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mlx5_class_attributes ; 

int mlx5_ib_stage_class_attr_init(struct mlx5_ib_dev *dev)
{
	int err;
	int i;

	for (i = 0; i < ARRAY_SIZE(mlx5_class_attributes); i++) {
		err = device_create_file(&dev->ib_dev.dev,
					 mlx5_class_attributes[i]);
		if (err)
			return err;
	}

	return 0;
}