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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  reg ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*) ; 
 void* finddevice (char*) ; 
 int /*<<< orphan*/  getprop (void*,char*,scalar_t__*,int) ; 
 scalar_t__ ibm4xx_memstart ; 
 int /*<<< orphan*/  ibm4xx_sdram_fixup_memsize () ; 

__attribute__((used)) static void iss_4xx_fixups(void)
{
	void *memory;
	u32 reg[3];

	memory = finddevice("/memory");
	if (!memory)
		fatal("Can't find memory node\n");
	/* This assumes #address-cells = 2, #size-cells =1 and that */
	getprop(memory, "reg", reg, sizeof(reg));
	if (reg[2])
		/* If the device tree specifies the memory range, use it */
		ibm4xx_memstart = reg[1];
	else
		/* othersize, read it from the SDRAM controller */
		ibm4xx_sdram_fixup_memsize();
}