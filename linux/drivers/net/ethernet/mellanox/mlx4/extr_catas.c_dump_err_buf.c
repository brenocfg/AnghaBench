#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ map; } ;
struct TYPE_3__ {int catas_size; } ;
struct mlx4_priv {TYPE_2__ catas_err; TYPE_1__ fw; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,...) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  swab32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_err_buf(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);

	int i;

	mlx4_err(dev, "Internal error detected:\n");
	for (i = 0; i < priv->fw.catas_size; ++i)
		mlx4_err(dev, "  buf[%02x]: %08x\n",
			 i, swab32(readl(priv->catas_err.map + i)));
}