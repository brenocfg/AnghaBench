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
struct bnxt_qplib_res {int /*<<< orphan*/  sgid_tbl; int /*<<< orphan*/  pkey_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_qplib_cleanup_pkey_tbl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_qplib_cleanup_sgid_tbl (struct bnxt_qplib_res*,int /*<<< orphan*/ *) ; 

void bnxt_qplib_cleanup_res(struct bnxt_qplib_res *res)
{
	bnxt_qplib_cleanup_pkey_tbl(&res->pkey_tbl);
	bnxt_qplib_cleanup_sgid_tbl(res, &res->sgid_tbl);
}