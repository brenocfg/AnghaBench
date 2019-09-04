#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int x; int y; } ;
struct TYPE_5__ {TYPE_1__ p0; } ;
struct tiler_block {size_t fmt; TYPE_2__ area; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_6__ {int slot_w; int slot_h; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ TILVIEW_8BIT ; 
 TYPE_3__* geom ; 
 scalar_t__ tiler_get_address (size_t,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  validfmt (size_t) ; 

dma_addr_t tiler_ssptr(struct tiler_block *block)
{
	BUG_ON(!validfmt(block->fmt));

	return TILVIEW_8BIT + tiler_get_address(block->fmt, 0,
			block->area.p0.x * geom[block->fmt].slot_w,
			block->area.p0.y * geom[block->fmt].slot_h);
}