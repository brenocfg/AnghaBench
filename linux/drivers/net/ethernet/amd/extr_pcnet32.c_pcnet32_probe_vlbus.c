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
 int /*<<< orphan*/  PCNET32_TOTAL_SIZE ; 
 int inb (unsigned int) ; 
 int /*<<< orphan*/  pcnet32_probe1 (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_region (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ request_region (unsigned int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void pcnet32_probe_vlbus(unsigned int *pcnet32_portlist)
{
	unsigned int *port, ioaddr;

	/* search for PCnet32 VLB cards at known addresses */
	for (port = pcnet32_portlist; (ioaddr = *port); port++) {
		if (request_region
		    (ioaddr, PCNET32_TOTAL_SIZE, "pcnet32_probe_vlbus")) {
			/* check if there is really a pcnet chip on that ioaddr */
			if ((inb(ioaddr + 14) == 0x57) &&
			    (inb(ioaddr + 15) == 0x57)) {
				pcnet32_probe1(ioaddr, 0, NULL);
			} else {
				release_region(ioaddr, PCNET32_TOTAL_SIZE);
			}
		}
	}
}