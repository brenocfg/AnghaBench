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
struct mlx5_flow_table {int dummy; } ;
struct fs_prio {int dummy; } ;

/* Variables and functions */
 struct mlx5_flow_table* find_closest_ft (struct fs_prio*,int) ; 

__attribute__((used)) static struct mlx5_flow_table *find_prev_chained_ft(struct fs_prio *prio)
{
	return find_closest_ft(prio, true);
}