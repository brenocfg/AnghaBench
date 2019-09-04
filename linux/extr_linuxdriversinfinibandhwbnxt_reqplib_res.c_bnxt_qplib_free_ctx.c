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
struct pci_dev {int dummy; } ;
struct bnxt_qplib_ctx {int /*<<< orphan*/  stats; int /*<<< orphan*/  tqm_pde; int /*<<< orphan*/ * tqm_tbl; int /*<<< orphan*/  tim_tbl; int /*<<< orphan*/  cq_tbl; int /*<<< orphan*/  srqc_tbl; int /*<<< orphan*/  mrw_tbl; int /*<<< orphan*/  qpc_tbl; } ;

/* Variables and functions */
 int MAX_TQM_ALLOC_REQ ; 
 int /*<<< orphan*/  bnxt_qplib_free_hwq (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_qplib_free_stats_ctx (struct pci_dev*,int /*<<< orphan*/ *) ; 

void bnxt_qplib_free_ctx(struct pci_dev *pdev,
			 struct bnxt_qplib_ctx *ctx)
{
	int i;

	bnxt_qplib_free_hwq(pdev, &ctx->qpc_tbl);
	bnxt_qplib_free_hwq(pdev, &ctx->mrw_tbl);
	bnxt_qplib_free_hwq(pdev, &ctx->srqc_tbl);
	bnxt_qplib_free_hwq(pdev, &ctx->cq_tbl);
	bnxt_qplib_free_hwq(pdev, &ctx->tim_tbl);
	for (i = 0; i < MAX_TQM_ALLOC_REQ; i++)
		bnxt_qplib_free_hwq(pdev, &ctx->tqm_tbl[i]);
	bnxt_qplib_free_hwq(pdev, &ctx->tqm_pde);
	bnxt_qplib_free_stats_ctx(pdev, &ctx->stats);
}