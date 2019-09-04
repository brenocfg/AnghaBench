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
struct rhashtable {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _mlx5e_tc_del_flow ; 
 int /*<<< orphan*/  rhashtable_free_and_destroy (struct rhashtable*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mlx5e_tc_esw_cleanup(struct rhashtable *tc_ht)
{
	rhashtable_free_and_destroy(tc_ht, _mlx5e_tc_del_flow, NULL);
}