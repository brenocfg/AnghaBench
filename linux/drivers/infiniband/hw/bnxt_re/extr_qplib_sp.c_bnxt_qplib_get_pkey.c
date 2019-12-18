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
typedef  int u16 ;
struct bnxt_qplib_res {TYPE_1__* pdev; } ;
struct bnxt_qplib_pkey_tbl {int max; int /*<<< orphan*/ * tbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 

int bnxt_qplib_get_pkey(struct bnxt_qplib_res *res,
			struct bnxt_qplib_pkey_tbl *pkey_tbl, u16 index,
			u16 *pkey)
{
	if (index == 0xFFFF) {
		*pkey = 0xFFFF;
		return 0;
	}
	if (index >= pkey_tbl->max) {
		dev_err(&res->pdev->dev,
			"Index %d exceeded PKEY table max (%d)\n",
			index, pkey_tbl->max);
		return -EINVAL;
	}
	memcpy(pkey, &pkey_tbl->tbl[index], sizeof(*pkey));
	return 0;
}