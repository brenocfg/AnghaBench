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
typedef  int /*<<< orphan*/  u16 ;
struct bnxt_qplib_res {int dummy; } ;
struct bnxt_qplib_pkey_tbl {int /*<<< orphan*/  max; int /*<<< orphan*/  tbl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_qplib_alloc_pkey_tbl(struct bnxt_qplib_res *res,
				     struct bnxt_qplib_pkey_tbl *pkey_tbl,
				     u16 max)
{
	pkey_tbl->tbl = kcalloc(max, sizeof(u16), GFP_KERNEL);
	if (!pkey_tbl->tbl)
		return -ENOMEM;

	pkey_tbl->max = max;
	return 0;
}