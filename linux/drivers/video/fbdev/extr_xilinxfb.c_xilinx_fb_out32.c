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
struct xilinxfb_drvdata {int flags; int /*<<< orphan*/  dcr_host; scalar_t__ regs; } ;

/* Variables and functions */
 int BUS_ACCESS_FLAG ; 
 int LITTLE_ENDIAN_ACCESS ; 
 int /*<<< orphan*/  dcr_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  iowrite32be (int,scalar_t__) ; 

__attribute__((used)) static void xilinx_fb_out32(struct xilinxfb_drvdata *drvdata, u32 offset,
			    u32 val)
{
	if (drvdata->flags & BUS_ACCESS_FLAG) {
		if (drvdata->flags & LITTLE_ENDIAN_ACCESS)
			iowrite32(val, drvdata->regs + (offset << 2));
		else
			iowrite32be(val, drvdata->regs + (offset << 2));
	}
#ifdef CONFIG_PPC_DCR
	else
		dcr_write(drvdata->dcr_host, offset, val);
#endif
}