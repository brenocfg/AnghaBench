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
typedef  size_t u32 ;
struct bnxt_qplib_dpi_tbl {size_t max; scalar_t__ unmapped_dbr; scalar_t__ dbr_bar_reg_iomem; void** app_tbl; int /*<<< orphan*/  tbl; } ;
struct bnxt_qplib_dpi {size_t dpi; scalar_t__ umdbr; scalar_t__ dbr; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  clear_bit (size_t,int /*<<< orphan*/ ) ; 
 size_t find_first_bit (int /*<<< orphan*/ ,size_t) ; 

int bnxt_qplib_alloc_dpi(struct bnxt_qplib_dpi_tbl *dpit,
			 struct bnxt_qplib_dpi     *dpi,
			 void                      *app)
{
	u32 bit_num;

	bit_num = find_first_bit(dpit->tbl, dpit->max);
	if (bit_num == dpit->max)
		return -ENOMEM;

	/* Found unused DPI */
	clear_bit(bit_num, dpit->tbl);
	dpit->app_tbl[bit_num] = app;

	dpi->dpi = bit_num;
	dpi->dbr = dpit->dbr_bar_reg_iomem + (bit_num * PAGE_SIZE);
	dpi->umdbr = dpit->unmapped_dbr + (bit_num * PAGE_SIZE);

	return 0;
}