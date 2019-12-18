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
struct TYPE_2__ {int /*<<< orphan*/  mkey_table; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  XA_FLAGS_LOCK_IRQ ; 
 int /*<<< orphan*/  xa_init_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mlx5_init_mkey_table(struct mlx5_core_dev *dev)
{
	xa_init_flags(&dev->priv.mkey_table, XA_FLAGS_LOCK_IRQ);
}