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
struct mlx5e_channels {int num; TYPE_1__** c; } ;
struct TYPE_2__ {int /*<<< orphan*/  rq; } ;

/* Variables and functions */
 int mlx5e_modify_rq_scatter_fcs (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mlx5e_modify_channels_scatter_fcs(struct mlx5e_channels *chs, bool enable)
{
	int err = 0;
	int i;

	for (i = 0; i < chs->num; i++) {
		err = mlx5e_modify_rq_scatter_fcs(&chs->c[i]->rq, enable);
		if (err)
			return err;
	}

	return 0;
}