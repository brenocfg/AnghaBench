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
struct bnxt_qplib_res {int /*<<< orphan*/  pdev; } ;
struct bnxt_qplib_dpi_tbl {scalar_t__ dbr_bar_reg_iomem; int /*<<< orphan*/  app_tbl; int /*<<< orphan*/  tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bnxt_qplib_dpi_tbl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_iounmap (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void bnxt_qplib_free_dpi_tbl(struct bnxt_qplib_res     *res,
				    struct bnxt_qplib_dpi_tbl *dpit)
{
	kfree(dpit->tbl);
	kfree(dpit->app_tbl);
	if (dpit->dbr_bar_reg_iomem)
		pci_iounmap(res->pdev, dpit->dbr_bar_reg_iomem);
	memset(dpit, 0, sizeof(*dpit));
}