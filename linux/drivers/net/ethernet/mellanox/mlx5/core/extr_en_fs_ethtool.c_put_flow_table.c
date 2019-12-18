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
struct mlx5e_ethtool_table {int /*<<< orphan*/ * ft; int /*<<< orphan*/  num_rules; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_destroy_flow_table (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_flow_table(struct mlx5e_ethtool_table *eth_ft)
{
	if (!--eth_ft->num_rules) {
		mlx5_destroy_flow_table(eth_ft->ft);
		eth_ft->ft = NULL;
	}
}