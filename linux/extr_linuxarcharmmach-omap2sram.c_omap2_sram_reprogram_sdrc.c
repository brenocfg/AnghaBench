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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  _omap2_sram_reprogram_sdrc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void omap2_sram_reprogram_sdrc(u32 perf_level, u32 dll_val, u32 mem_type)
{
	BUG_ON(!_omap2_sram_reprogram_sdrc);
	_omap2_sram_reprogram_sdrc(perf_level, dll_val, mem_type);
}