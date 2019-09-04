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
struct omap_aes_dev {TYPE_1__* pdata; } ;
struct TYPE_2__ {int dma_enable_out; int dma_enable_in; int dma_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_REG_MASK (struct omap_aes_dev*) ; 
 int /*<<< orphan*/  omap_aes_write_mask (struct omap_aes_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void omap_aes_dma_stop(struct omap_aes_dev *dd)
{
	u32 mask;

	mask = dd->pdata->dma_enable_out | dd->pdata->dma_enable_in |
	       dd->pdata->dma_start;

	omap_aes_write_mask(dd, AES_REG_MASK(dd), 0, mask);
}