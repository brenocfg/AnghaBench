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

/* Variables and functions */
 int COLOR ; 
 int CPC ; 
 int /*<<< orphan*/  dma_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void omap1_clear_lch_regs(int lch)
{
	int i;

	for (i = CPC; i <= COLOR; i += 1)
		dma_write(0, i, lch);
}