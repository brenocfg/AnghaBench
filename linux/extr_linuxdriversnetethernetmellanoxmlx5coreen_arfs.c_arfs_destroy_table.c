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
struct arfs_table {int /*<<< orphan*/  ft; int /*<<< orphan*/  default_rule; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_del_flow_rules (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_destroy_flow_table (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void arfs_destroy_table(struct arfs_table *arfs_t)
{
	mlx5_del_flow_rules(arfs_t->default_rule);
	mlx5e_destroy_flow_table(&arfs_t->ft);
}