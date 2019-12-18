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
struct net_device {int dummy; } ;
struct mlx4_en_priv {int* maxrate; } ;
struct ieee_maxrate {int* tc_maxrate; } ;

/* Variables and functions */
 int IEEE_8021QAZ_MAX_TCS ; 
 int MLX4_RATELIMIT_UNITS_IN_KB ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_dcbnl_ieee_getmaxrate(struct net_device *dev,
				   struct ieee_maxrate *maxrate)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	int i;

	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
		maxrate->tc_maxrate[i] =
			priv->maxrate[i] * MLX4_RATELIMIT_UNITS_IN_KB;

	return 0;
}