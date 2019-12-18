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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_mkey {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int mlx5_core_create_mkey_cb (struct mlx5_core_dev*,struct mlx5_core_mkey*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int mlx5_core_create_mkey(struct mlx5_core_dev *dev,
			  struct mlx5_core_mkey *mkey,
			  u32 *in, int inlen)
{
	return mlx5_core_create_mkey_cb(dev, mkey, NULL, in, inlen,
					NULL, 0, NULL, NULL);
}