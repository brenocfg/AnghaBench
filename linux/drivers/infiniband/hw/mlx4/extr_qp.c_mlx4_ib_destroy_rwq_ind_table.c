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
struct ib_rwq_ind_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ib_rwq_ind_table*) ; 

int mlx4_ib_destroy_rwq_ind_table(struct ib_rwq_ind_table *ib_rwq_ind_tbl)
{
	kfree(ib_rwq_ind_tbl);
	return 0;
}