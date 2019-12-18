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
struct mlx5e_priv {int /*<<< orphan*/  tls; } ;

/* Variables and functions */
 int NUM_TLS_SW_COUNTERS ; 

int mlx5e_tls_get_count(struct mlx5e_priv *priv)
{
	if (!priv->tls)
		return 0;

	return NUM_TLS_SW_COUNTERS;
}