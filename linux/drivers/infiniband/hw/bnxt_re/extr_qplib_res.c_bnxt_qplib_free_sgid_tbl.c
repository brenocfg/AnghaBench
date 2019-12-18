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
struct bnxt_qplib_sgid_tbl {scalar_t__ active; scalar_t__ max; int /*<<< orphan*/ * vlan; int /*<<< orphan*/ * ctx; int /*<<< orphan*/ * hw_id; int /*<<< orphan*/ * tbl; } ;
struct bnxt_qplib_res {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_qplib_free_sgid_tbl(struct bnxt_qplib_res *res,
				     struct bnxt_qplib_sgid_tbl *sgid_tbl)
{
	kfree(sgid_tbl->tbl);
	kfree(sgid_tbl->hw_id);
	kfree(sgid_tbl->ctx);
	kfree(sgid_tbl->vlan);
	sgid_tbl->tbl = NULL;
	sgid_tbl->hw_id = NULL;
	sgid_tbl->ctx = NULL;
	sgid_tbl->vlan = NULL;
	sgid_tbl->max = 0;
	sgid_tbl->active = 0;
}