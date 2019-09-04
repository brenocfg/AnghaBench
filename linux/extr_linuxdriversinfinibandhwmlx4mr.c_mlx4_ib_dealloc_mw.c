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
struct mlx4_ib_mw {int /*<<< orphan*/  mmw; } ;
struct ib_mw {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx4_ib_mw*) ; 
 int /*<<< orphan*/  mlx4_mw_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx4_ib_mw* to_mmw (struct ib_mw*) ; 

int mlx4_ib_dealloc_mw(struct ib_mw *ibmw)
{
	struct mlx4_ib_mw *mw = to_mmw(ibmw);

	mlx4_mw_free(to_mdev(ibmw->device)->dev, &mw->mmw);
	kfree(mw);

	return 0;
}