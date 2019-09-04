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
struct bnxt_qplib_res {int /*<<< orphan*/ * pdev; int /*<<< orphan*/ * netdev; int /*<<< orphan*/  dpi_tbl; int /*<<< orphan*/  pd_tbl; int /*<<< orphan*/  sgid_tbl; int /*<<< orphan*/  pkey_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_qplib_free_dpi_tbl (struct bnxt_qplib_res*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_qplib_free_pd_tbl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_qplib_free_pkey_tbl (struct bnxt_qplib_res*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_qplib_free_sgid_tbl (struct bnxt_qplib_res*,int /*<<< orphan*/ *) ; 

void bnxt_qplib_free_res(struct bnxt_qplib_res *res)
{
	bnxt_qplib_free_pkey_tbl(res, &res->pkey_tbl);
	bnxt_qplib_free_sgid_tbl(res, &res->sgid_tbl);
	bnxt_qplib_free_pd_tbl(&res->pd_tbl);
	bnxt_qplib_free_dpi_tbl(res, &res->dpi_tbl);

	res->netdev = NULL;
	res->pdev = NULL;
}