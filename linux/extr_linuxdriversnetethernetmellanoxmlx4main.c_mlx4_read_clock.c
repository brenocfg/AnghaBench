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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct mlx4_priv {scalar_t__ clock_mapping; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 scalar_t__ swab32 (int /*<<< orphan*/ ) ; 

u64 mlx4_read_clock(struct mlx4_dev *dev)
{
	u32 clockhi, clocklo, clockhi1;
	u64 cycles;
	int i;
	struct mlx4_priv *priv = mlx4_priv(dev);

	for (i = 0; i < 10; i++) {
		clockhi = swab32(readl(priv->clock_mapping));
		clocklo = swab32(readl(priv->clock_mapping + 4));
		clockhi1 = swab32(readl(priv->clock_mapping));
		if (clockhi == clockhi1)
			break;
	}

	cycles = (u64) clockhi << 32 | (u64) clocklo;

	return cycles;
}