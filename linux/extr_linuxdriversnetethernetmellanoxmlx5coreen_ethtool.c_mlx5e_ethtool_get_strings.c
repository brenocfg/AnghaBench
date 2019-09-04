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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct mlx5e_priv {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ETH_GSTRING_LEN ; 
#define  ETH_SS_PRIV_FLAGS 130 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int /*<<< orphan*/  mlx5e_fill_stats_strings (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mlx5e_priv_flags ; 
 int mlx5e_self_test_num (struct mlx5e_priv*) ; 
 int /*<<< orphan*/ * mlx5e_self_tests ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mlx5e_ethtool_get_strings(struct mlx5e_priv *priv, u32 stringset, u8 *data)
{
	int i;

	switch (stringset) {
	case ETH_SS_PRIV_FLAGS:
		for (i = 0; i < ARRAY_SIZE(mlx5e_priv_flags); i++)
			strcpy(data + i * ETH_GSTRING_LEN, mlx5e_priv_flags[i]);
		break;

	case ETH_SS_TEST:
		for (i = 0; i < mlx5e_self_test_num(priv); i++)
			strcpy(data + i * ETH_GSTRING_LEN,
			       mlx5e_self_tests[i]);
		break;

	case ETH_SS_STATS:
		mlx5e_fill_stats_strings(priv, data);
		break;
	}
}