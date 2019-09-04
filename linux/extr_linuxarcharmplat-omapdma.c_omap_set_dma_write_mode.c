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
typedef  enum omap_dma_write_mode { ____Placeholder_omap_dma_write_mode } omap_dma_write_mode ;
struct TYPE_2__ {int (* dma_read ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* dma_write ) (int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CSDP ; 
 scalar_t__ dma_omap2plus () ; 
 TYPE_1__* p ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ,int) ; 

void omap_set_dma_write_mode(int lch, enum omap_dma_write_mode mode)
{
	if (dma_omap2plus()) {
		u32 csdp;

		csdp = p->dma_read(CSDP, lch);
		csdp &= ~(0x3 << 16);
		csdp |= (mode << 16);
		p->dma_write(csdp, CSDP, lch);
	}
}