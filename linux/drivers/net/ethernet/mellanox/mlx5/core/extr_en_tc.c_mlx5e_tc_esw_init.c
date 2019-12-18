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
 int rhashtable_init (struct rhashtable*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc_ht_params ; 

int mlx5e_tc_esw_init(struct rhashtable *tc_ht)
{
	return rhashtable_init(tc_ht, &tc_ht_params);
}