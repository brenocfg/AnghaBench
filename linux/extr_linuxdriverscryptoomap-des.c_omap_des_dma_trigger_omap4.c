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
typedef  int u32 ;
struct omap_des_dev {TYPE_1__* pdata; int /*<<< orphan*/ * dma_lch_in; int /*<<< orphan*/ * dma_lch_out; } ;
struct TYPE_2__ {int dma_start; int dma_enable_out; int dma_enable_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  DES_REG_LENGTH_N (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DES_REG_MASK (struct omap_des_dev*) ; 
 int /*<<< orphan*/  omap_des_write (struct omap_des_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omap_des_write_mask (struct omap_des_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void omap_des_dma_trigger_omap4(struct omap_des_dev *dd, int length)
{
	u32 mask, val;

	omap_des_write(dd, DES_REG_LENGTH_N(0), length);

	val = dd->pdata->dma_start;

	if (dd->dma_lch_out != NULL)
		val |= dd->pdata->dma_enable_out;
	if (dd->dma_lch_in != NULL)
		val |= dd->pdata->dma_enable_in;

	mask = dd->pdata->dma_enable_out | dd->pdata->dma_enable_in |
	       dd->pdata->dma_start;

	omap_des_write_mask(dd, DES_REG_MASK(dd), val, mask);
}