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
typedef  int u16 ;
struct bnxt_qplib_res {int dummy; } ;
struct bnxt_qplib_pkey_tbl {int max; int /*<<< orphan*/  tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_qplib_add_pkey (struct bnxt_qplib_res*,struct bnxt_qplib_pkey_tbl*,int*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnxt_qplib_init_pkey_tbl(struct bnxt_qplib_res *res,
				     struct bnxt_qplib_pkey_tbl *pkey_tbl)
{
	u16 pkey = 0xFFFF;

	memset(pkey_tbl->tbl, 0, sizeof(u16) * pkey_tbl->max);

	/* pkey default = 0xFFFF */
	bnxt_qplib_add_pkey(res, pkey_tbl, &pkey, false);
}