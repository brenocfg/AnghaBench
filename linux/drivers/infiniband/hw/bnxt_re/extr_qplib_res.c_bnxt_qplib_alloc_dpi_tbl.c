#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct bnxt_qplib_res {TYPE_1__* pdev; } ;
struct bnxt_qplib_dpi_tbl {int unmapped_dbr; int max; int /*<<< orphan*/  dbr_bar_reg_iomem; scalar_t__ tbl; int /*<<< orphan*/ * app_tbl; } ;
typedef  int resource_size_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EALREADY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int RCFW_DBR_PCI_BAR_REGION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ioremap_nocache (int,int) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 scalar_t__ kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pci_iounmap (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int pci_resource_len (TYPE_1__*,int) ; 
 int pci_resource_start (TYPE_1__*,int) ; 

__attribute__((used)) static int bnxt_qplib_alloc_dpi_tbl(struct bnxt_qplib_res     *res,
				    struct bnxt_qplib_dpi_tbl *dpit,
				    u32                       dbr_offset)
{
	u32 dbr_bar_reg = RCFW_DBR_PCI_BAR_REGION;
	resource_size_t bar_reg_base;
	u32 dbr_len, bytes;

	if (dpit->dbr_bar_reg_iomem) {
		dev_err(&res->pdev->dev, "DBR BAR region %d already mapped\n",
			dbr_bar_reg);
		return -EALREADY;
	}

	bar_reg_base = pci_resource_start(res->pdev, dbr_bar_reg);
	if (!bar_reg_base) {
		dev_err(&res->pdev->dev, "BAR region %d resc start failed\n",
			dbr_bar_reg);
		return -ENOMEM;
	}

	dbr_len = pci_resource_len(res->pdev, dbr_bar_reg) - dbr_offset;
	if (!dbr_len || ((dbr_len & (PAGE_SIZE - 1)) != 0)) {
		dev_err(&res->pdev->dev, "Invalid DBR length %d\n", dbr_len);
		return -ENOMEM;
	}

	dpit->dbr_bar_reg_iomem = ioremap_nocache(bar_reg_base + dbr_offset,
						  dbr_len);
	if (!dpit->dbr_bar_reg_iomem) {
		dev_err(&res->pdev->dev,
			"FP: DBR BAR region %d mapping failed\n", dbr_bar_reg);
		return -ENOMEM;
	}

	dpit->unmapped_dbr = bar_reg_base + dbr_offset;
	dpit->max = dbr_len / PAGE_SIZE;

	dpit->app_tbl = kcalloc(dpit->max, sizeof(void *), GFP_KERNEL);
	if (!dpit->app_tbl)
		goto unmap_io;

	bytes = dpit->max >> 3;
	if (!bytes)
		bytes = 1;

	dpit->tbl = kmalloc(bytes, GFP_KERNEL);
	if (!dpit->tbl) {
		kfree(dpit->app_tbl);
		dpit->app_tbl = NULL;
		goto unmap_io;
	}

	memset((u8 *)dpit->tbl, 0xFF, bytes);

	return 0;

unmap_io:
	pci_iounmap(res->pdev, dpit->dbr_bar_reg_iomem);
	return -ENOMEM;
}