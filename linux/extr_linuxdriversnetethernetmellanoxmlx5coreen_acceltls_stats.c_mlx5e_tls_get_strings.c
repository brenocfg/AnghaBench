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
typedef  int /*<<< orphan*/  uint8_t ;
struct mlx5e_priv {int /*<<< orphan*/  tls; } ;
struct TYPE_2__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
 unsigned int NUM_TLS_SW_COUNTERS ; 
 TYPE_1__* mlx5e_tls_sw_stats_desc ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int mlx5e_tls_get_strings(struct mlx5e_priv *priv, uint8_t *data)
{
	unsigned int i, idx = 0;

	if (!priv->tls)
		return 0;

	for (i = 0; i < NUM_TLS_SW_COUNTERS; i++)
		strcpy(data + (idx++) * ETH_GSTRING_LEN,
		       mlx5e_tls_sw_stats_desc[i].format);

	return NUM_TLS_SW_COUNTERS;
}