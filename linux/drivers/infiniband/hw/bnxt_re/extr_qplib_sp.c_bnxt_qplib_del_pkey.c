#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct bnxt_qplib_res {TYPE_1__* pdev; } ;
struct bnxt_qplib_pkey_tbl {int max; int /*<<< orphan*/  active; int /*<<< orphan*/ * tbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int bnxt_qplib_del_pkey(struct bnxt_qplib_res *res,
			struct bnxt_qplib_pkey_tbl *pkey_tbl, u16 *pkey,
			bool update)
{
	int i, rc = 0;

	if (!pkey_tbl) {
		dev_err(&res->pdev->dev, "PKEY table not allocated\n");
		return -EINVAL;
	}

	/* Do we need a pkey_lock here? */
	if (!pkey_tbl->active) {
		dev_err(&res->pdev->dev, "PKEY table has no active entries\n");
		return -ENOMEM;
	}
	for (i = 0; i < pkey_tbl->max; i++) {
		if (!memcmp(&pkey_tbl->tbl[i], pkey, sizeof(*pkey)))
			break;
	}
	if (i == pkey_tbl->max) {
		dev_err(&res->pdev->dev,
			"PKEY 0x%04x not found in the pkey table\n", *pkey);
		return -ENOMEM;
	}
	memset(&pkey_tbl->tbl[i], 0, sizeof(*pkey));
	pkey_tbl->active--;

	/* unlock */
	return rc;
}