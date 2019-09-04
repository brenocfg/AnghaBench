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
struct io_pgtable_cfg {int dummy; } ;
typedef  int /*<<< orphan*/  arm_v7s_iopte ;

/* Variables and functions */
 int /*<<< orphan*/  __arm_v7s_pte_sync (int /*<<< orphan*/ *,int,struct io_pgtable_cfg*) ; 

__attribute__((used)) static void __arm_v7s_set_pte(arm_v7s_iopte *ptep, arm_v7s_iopte pte,
			      int num_entries, struct io_pgtable_cfg *cfg)
{
	int i;

	for (i = 0; i < num_entries; i++)
		ptep[i] = pte;

	__arm_v7s_pte_sync(ptep, num_entries, cfg);
}