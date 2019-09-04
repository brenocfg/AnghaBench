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
struct TYPE_2__ {int (* dma_read ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* dma_write ) (int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CSDP ; 
 TYPE_1__* p ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ,int) ; 

void omap_set_dma_dest_data_pack(int lch, int enable)
{
	u32 l;

	l = p->dma_read(CSDP, lch);
	l &= ~(1 << 13);
	if (enable)
		l |= 1 << 13;
	p->dma_write(l, CSDP, lch);
}