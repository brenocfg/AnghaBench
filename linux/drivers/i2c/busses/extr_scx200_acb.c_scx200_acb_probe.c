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
typedef  int u8 ;
struct scx200_acb_iface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACBCTL1 ; 
 int ACBCTL1_NMINTE ; 
 int /*<<< orphan*/  ACBCTL2 ; 
 int ACBCTL2_ENABLE ; 
 int ENXIO ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static int scx200_acb_probe(struct scx200_acb_iface *iface)
{
	u8 val;

	/* Disable the ACCESS.bus device and Configure the SCL
	   frequency: 16 clock cycles */
	outb(0x70, ACBCTL2);

	if (inb(ACBCTL2) != 0x70) {
		pr_debug("ACBCTL2 readback failed\n");
		return -ENXIO;
	}

	outb(inb(ACBCTL1) | ACBCTL1_NMINTE, ACBCTL1);

	val = inb(ACBCTL1);
	if (val) {
		pr_debug("disabled, but ACBCTL1=0x%02x\n", val);
		return -ENXIO;
	}

	outb(inb(ACBCTL2) | ACBCTL2_ENABLE, ACBCTL2);

	outb(inb(ACBCTL1) | ACBCTL1_NMINTE, ACBCTL1);

	val = inb(ACBCTL1);
	if ((val & ACBCTL1_NMINTE) != ACBCTL1_NMINTE) {
		pr_debug("enabled, but NMINTE won't be set, ACBCTL1=0x%02x\n",
			 val);
		return -ENXIO;
	}

	return 0;
}