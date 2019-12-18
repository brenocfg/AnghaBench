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
struct mlx5e_channels {int num; int /*<<< orphan*/ * c; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_activate_channel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_activate_channels(struct mlx5e_channels *chs)
{
	int i;

	for (i = 0; i < chs->num; i++)
		mlx5e_activate_channel(chs->c[i]);
}