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
struct mlx4_dev {int /*<<< orphan*/  num_slaves; TYPE_1__* persist; } ;
struct TYPE_2__ {int num_vfs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,int,int /*<<< orphan*/ ) ; 

int mlx4_get_vf_indx(struct mlx4_dev *dev, int slave)
{
	if (slave < 1 || slave > dev->persist->num_vfs) {
		mlx4_err(dev,
			 "Bad slave number:%d (number of activated slaves: %lu)\n",
			 slave, dev->num_slaves);
		return -EINVAL;
	}
	return slave - 1;
}