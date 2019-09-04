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
 int IMX_CHIP_REVISION_1_0 ; 
 int IMX_CHIP_REVISION_2_0 ; 
 int IMX_CHIP_REVISION_2_1 ; 
 int IMX_CHIP_REVISION_UNKNOWN ; 
 scalar_t__ MX35_IIM_BASE_ADDR ; 
 int /*<<< orphan*/  MX35_IO_ADDRESS (scalar_t__) ; 
 scalar_t__ MXC_IIMSREV ; 
 int imx_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mx35_read_cpu_rev(void)
{
	u32 rev;

	rev = imx_readl(MX35_IO_ADDRESS(MX35_IIM_BASE_ADDR + MXC_IIMSREV));
	switch (rev) {
	case 0x00:
		return IMX_CHIP_REVISION_1_0;
	case 0x10:
		return IMX_CHIP_REVISION_2_0;
	case 0x11:
		return IMX_CHIP_REVISION_2_1;
	default:
		return IMX_CHIP_REVISION_UNKNOWN;
	}
}