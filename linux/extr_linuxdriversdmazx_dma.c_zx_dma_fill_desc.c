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
struct zx_dma_desc_sw {int desc_num; TYPE_1__* desc_hw; scalar_t__ desc_hw_lli; } ;
struct zx_desc_hw {int dummy; } ;
typedef  void* dma_addr_t ;
struct TYPE_2__ {size_t src_x; int ctr; void* daddr; void* saddr; scalar_t__ lli; } ;

/* Variables and functions */

__attribute__((used)) static void zx_dma_fill_desc(struct zx_dma_desc_sw *ds, dma_addr_t dst,
			     dma_addr_t src, size_t len, u32 num, u32 ccfg)
{
	if ((num + 1) < ds->desc_num)
		ds->desc_hw[num].lli = ds->desc_hw_lli + (num + 1) *
			sizeof(struct zx_desc_hw);
	ds->desc_hw[num].saddr = src;
	ds->desc_hw[num].daddr = dst;
	ds->desc_hw[num].src_x = len;
	ds->desc_hw[num].ctr = ccfg;
}