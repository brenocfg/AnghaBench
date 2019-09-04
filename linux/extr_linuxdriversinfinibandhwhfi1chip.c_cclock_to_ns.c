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
struct hfi1_devdata {scalar_t__ icode; } ;

/* Variables and functions */
 int ASIC_CCLOCK_PS ; 
 int FPGA_CCLOCK_PS ; 
 scalar_t__ ICODE_FPGA_EMULATION ; 

u32 cclock_to_ns(struct hfi1_devdata *dd, u32 cclocks)
{
	u32 ns;

	if (dd->icode == ICODE_FPGA_EMULATION)
		ns = (cclocks * FPGA_CCLOCK_PS) / 1000;
	else  /* simulation pretends to be ASIC */
		ns = (cclocks * ASIC_CCLOCK_PS) / 1000;
	if (cclocks && !ns)
		ns = 1;
	return ns;
}