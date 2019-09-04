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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {scalar_t__ mchip_fnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCHIP_MM_FIR (int) ; 
 int /*<<< orphan*/  MCHIP_MM_PT_ADDR ; 
 int /*<<< orphan*/  mchip_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ meye ; 

__attribute__((used)) static void mchip_dma_setup(dma_addr_t dma_addr)
{
	int i;

	mchip_set(MCHIP_MM_PT_ADDR, (u32)dma_addr);
	for (i = 0; i < 4; i++)
		mchip_set(MCHIP_MM_FIR(i), 0);
	meye.mchip_fnum = 0;
}