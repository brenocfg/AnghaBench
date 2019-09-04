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
typedef  int /*<<< orphan*/  uint8_t ;
struct mlx5e_priv {int /*<<< orphan*/  ipsec; } ;
struct TYPE_4__ {int /*<<< orphan*/  format; } ;
struct TYPE_3__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
 int NUM_IPSEC_COUNTERS ; 
 unsigned int NUM_IPSEC_HW_COUNTERS ; 
 unsigned int NUM_IPSEC_SW_COUNTERS ; 
 TYPE_2__* mlx5e_ipsec_hw_stats_desc ; 
 TYPE_1__* mlx5e_ipsec_sw_stats_desc ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int mlx5e_ipsec_get_strings(struct mlx5e_priv *priv, uint8_t *data)
{
	unsigned int i, idx = 0;

	if (!priv->ipsec)
		return 0;

	for (i = 0; i < NUM_IPSEC_HW_COUNTERS; i++)
		strcpy(data + (idx++) * ETH_GSTRING_LEN,
		       mlx5e_ipsec_hw_stats_desc[i].format);

	for (i = 0; i < NUM_IPSEC_SW_COUNTERS; i++)
		strcpy(data + (idx++) * ETH_GSTRING_LEN,
		       mlx5e_ipsec_sw_stats_desc[i].format);

	return NUM_IPSEC_COUNTERS;
}