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
struct mlx5_eswitch {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ ESW_ALLOWED (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  MLX5_ESWITCH_NONE ; 

u8 mlx5_eswitch_mode(struct mlx5_eswitch *esw)
{
	return ESW_ALLOWED(esw) ? esw->mode : MLX5_ESWITCH_NONE;
}