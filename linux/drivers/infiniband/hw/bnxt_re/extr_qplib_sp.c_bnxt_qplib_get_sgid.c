#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bnxt_qplib_sgid_tbl {int max; TYPE_2__* tbl; } ;
struct bnxt_qplib_res {TYPE_1__* pdev; } ;
struct bnxt_qplib_gid {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  gid; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  memcpy (struct bnxt_qplib_gid*,int /*<<< orphan*/ *,int) ; 

int bnxt_qplib_get_sgid(struct bnxt_qplib_res *res,
			struct bnxt_qplib_sgid_tbl *sgid_tbl, int index,
			struct bnxt_qplib_gid *gid)
{
	if (index >= sgid_tbl->max) {
		dev_err(&res->pdev->dev,
			"Index %d exceeded SGID table max (%d)\n",
			index, sgid_tbl->max);
		return -EINVAL;
	}
	memcpy(gid, &sgid_tbl->tbl[index].gid, sizeof(*gid));
	return 0;
}