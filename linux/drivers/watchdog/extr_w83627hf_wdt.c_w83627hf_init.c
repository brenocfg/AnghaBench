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
struct watchdog_device {unsigned char timeout; } ;
typedef  enum chips { ____Placeholder_chips } chips ;

/* Variables and functions */
 int /*<<< orphan*/  W83627HF_LD_WDT ; 
 int cr_wdt_control ; 
 int cr_wdt_csr ; 
 int cr_wdt_timeout ; 
 scalar_t__ early_disable ; 
#define  nct6102 149 
#define  nct6775 148 
#define  nct6776 147 
#define  nct6779 146 
#define  nct6791 145 
#define  nct6792 144 
#define  nct6793 143 
#define  nct6795 142 
#define  nct6796 141 
 int /*<<< orphan*/  pr_info (char*,unsigned char) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int superio_enter () ; 
 int /*<<< orphan*/  superio_exit () ; 
 int superio_inb (int) ; 
 int /*<<< orphan*/  superio_outb (int,unsigned char) ; 
 int /*<<< orphan*/  superio_select (int /*<<< orphan*/ ) ; 
#define  w83627dhg 140 
#define  w83627dhg_p 139 
#define  w83627ehf 138 
#define  w83627hf 137 
#define  w83627s 136 
#define  w83627thf 135 
#define  w83627uhg 134 
#define  w83637hf 133 
#define  w83667hg 132 
#define  w83667hg_b 131 
#define  w83687thf 130 
#define  w83697hf 129 
#define  w83697ug 128 

__attribute__((used)) static int w83627hf_init(struct watchdog_device *wdog, enum chips chip)
{
	int ret;
	unsigned char t;

	ret = superio_enter();
	if (ret)
		return ret;

	superio_select(W83627HF_LD_WDT);

	/* set CR30 bit 0 to activate GPIO2 */
	t = superio_inb(0x30);
	if (!(t & 0x01))
		superio_outb(0x30, t | 0x01);

	switch (chip) {
	case w83627hf:
	case w83627s:
		t = superio_inb(0x2B) & ~0x10;
		superio_outb(0x2B, t); /* set GPIO24 to WDT0 */
		break;
	case w83697hf:
		/* Set pin 119 to WDTO# mode (= CR29, WDT0) */
		t = superio_inb(0x29) & ~0x60;
		t |= 0x20;
		superio_outb(0x29, t);
		break;
	case w83697ug:
		/* Set pin 118 to WDTO# mode */
		t = superio_inb(0x2b) & ~0x04;
		superio_outb(0x2b, t);
		break;
	case w83627thf:
		t = (superio_inb(0x2B) & ~0x08) | 0x04;
		superio_outb(0x2B, t); /* set GPIO3 to WDT0 */
		break;
	case w83627dhg:
	case w83627dhg_p:
		t = superio_inb(0x2D) & ~0x01; /* PIN77 -> WDT0# */
		superio_outb(0x2D, t); /* set GPIO5 to WDT0 */
		t = superio_inb(cr_wdt_control);
		t |= 0x02;	/* enable the WDTO# output low pulse
				 * to the KBRST# pin */
		superio_outb(cr_wdt_control, t);
		break;
	case w83637hf:
		break;
	case w83687thf:
		t = superio_inb(0x2C) & ~0x80; /* PIN47 -> WDT0# */
		superio_outb(0x2C, t);
		break;
	case w83627ehf:
	case w83627uhg:
	case w83667hg:
	case w83667hg_b:
	case nct6775:
	case nct6776:
	case nct6779:
	case nct6791:
	case nct6792:
	case nct6793:
	case nct6795:
	case nct6796:
	case nct6102:
		/*
		 * These chips have a fixed WDTO# output pin (W83627UHG),
		 * or support more than one WDTO# output pin.
		 * Don't touch its configuration, and hope the BIOS
		 * does the right thing.
		 */
		t = superio_inb(cr_wdt_control);
		t |= 0x02;	/* enable the WDTO# output low pulse
				 * to the KBRST# pin */
		superio_outb(cr_wdt_control, t);
		break;
	default:
		break;
	}

	t = superio_inb(cr_wdt_timeout);
	if (t != 0) {
		if (early_disable) {
			pr_warn("Stopping previously enabled watchdog until userland kicks in\n");
			superio_outb(cr_wdt_timeout, 0);
		} else {
			pr_info("Watchdog already running. Resetting timeout to %d sec\n",
				wdog->timeout);
			superio_outb(cr_wdt_timeout, wdog->timeout);
		}
	}

	/* set second mode & disable keyboard turning off watchdog */
	t = superio_inb(cr_wdt_control) & ~0x0C;
	superio_outb(cr_wdt_control, t);

	/* reset trigger, disable keyboard & mouse turning off watchdog */
	t = superio_inb(cr_wdt_csr) & ~0xD0;
	superio_outb(cr_wdt_csr, t);

	superio_exit();

	return 0;
}