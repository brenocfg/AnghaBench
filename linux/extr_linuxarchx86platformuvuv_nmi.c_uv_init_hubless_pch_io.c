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
 int* PCH_PCR_GPIO_ADDRESS (int) ; 
 int /*<<< orphan*/  nmi_debug (char*,int*,int,...) ; 
 int readl (int*) ; 
 int /*<<< orphan*/  writel (int,int*) ; 

__attribute__((used)) static void uv_init_hubless_pch_io(int offset, int mask, int data)
{
	int *addr = PCH_PCR_GPIO_ADDRESS(offset);
	int readd = readl(addr);

	if (mask) {			/* OR in new data */
		int writed = (readd & ~mask) | data;

		nmi_debug("UV:PCH: %p = %x & %x | %x (%x)\n",
			addr, readd, ~mask, data, writed);
		writel(writed, addr);
	} else if (readd & data) {	/* clear status bit */
		nmi_debug("UV:PCH: %p = %x\n", addr, data);
		writel(data, addr);
	}

	(void)readl(addr);		/* flush write data */
}