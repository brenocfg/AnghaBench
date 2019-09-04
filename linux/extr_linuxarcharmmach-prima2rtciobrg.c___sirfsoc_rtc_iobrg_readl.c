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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ SIRFSOC_CPUIOBRG_ADDR ; 
 scalar_t__ SIRFSOC_CPUIOBRG_CTRL ; 
 scalar_t__ SIRFSOC_CPUIOBRG_DATA ; 
 scalar_t__ SIRFSOC_CPUIOBRG_WRBE ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  sirfsoc_rtc_iobrg_wait_sync () ; 
 scalar_t__ sirfsoc_rtciobrg_base ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

u32 __sirfsoc_rtc_iobrg_readl(u32 addr)
{
	sirfsoc_rtc_iobrg_wait_sync();

	writel_relaxed(0x00, sirfsoc_rtciobrg_base + SIRFSOC_CPUIOBRG_WRBE);
	writel_relaxed(addr, sirfsoc_rtciobrg_base + SIRFSOC_CPUIOBRG_ADDR);
	writel_relaxed(0x01, sirfsoc_rtciobrg_base + SIRFSOC_CPUIOBRG_CTRL);

	sirfsoc_rtc_iobrg_wait_sync();

	return readl_relaxed(sirfsoc_rtciobrg_base + SIRFSOC_CPUIOBRG_DATA);
}