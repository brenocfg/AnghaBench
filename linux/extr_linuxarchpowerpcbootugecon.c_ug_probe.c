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
 void* ug_grab_exi_io_base () ; 
 void* ug_io_base ; 
 scalar_t__ ug_is_adapter_present () ; 

void *ug_probe(void)
{
	void *exi_io_base;
	int i;

	exi_io_base = ug_grab_exi_io_base();
	if (!exi_io_base)
		return NULL;

	/* look for a usbgecko on memcard slots A and B */
	for (i = 0; i < 2; i++) {
		ug_io_base = exi_io_base + 0x14 * i;
		if (ug_is_adapter_present())
			break;
	}
	if (i == 2)
		ug_io_base = NULL;
	return ug_io_base;
}