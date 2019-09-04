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
 int /*<<< orphan*/  DBG (char*,unsigned int) ; 
 unsigned int* IOP3XX_ATUISR ; 
 unsigned int* IOP3XX_ATUSR ; 

__attribute__((used)) static int iop3xx_pci_status(void)
{
	unsigned int status;
	int ret = 0;

	/*
	 * Check the status registers.
	 */
	status = *IOP3XX_ATUSR;
	if (status & 0xf900) {
		DBG("\t\t\tPCI: P0 - status = 0x%08x\n", status);
		*IOP3XX_ATUSR = status & 0xf900;
		ret = 1;
	}

	status = *IOP3XX_ATUISR;
	if (status & 0x679f) {
		DBG("\t\t\tPCI: P1 - status = 0x%08x\n", status);
		*IOP3XX_ATUISR = status & 0x679f;
		ret = 1;
	}

	return ret;
}