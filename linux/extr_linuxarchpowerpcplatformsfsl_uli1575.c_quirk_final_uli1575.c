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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMOS_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_24H ; 
 int RTC_ALARM_DONT_CARE ; 
 int /*<<< orphan*/  RTC_CONTROL ; 
 int /*<<< orphan*/  RTC_SET ; 
 int /*<<< orphan*/  RTC_VALID ; 
 int /*<<< orphan*/  is_quirk_valid () ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  outb_p (int,int) ; 

__attribute__((used)) static void quirk_final_uli1575(struct pci_dev *dev)
{
	/* Set i8259 interrupt trigger
	 * IRQ 3:  Level
	 * IRQ 4:  Level
	 * IRQ 5:  Level
	 * IRQ 6:  Level
	 * IRQ 7:  Level
	 * IRQ 9:  Level
	 * IRQ 10: Level
	 * IRQ 11: Level
	 * IRQ 12: Level
	 * IRQ 14: Edge
	 * IRQ 15: Edge
	 */
	if (!is_quirk_valid())
		return;

	outb(0xfa, 0x4d0);
	outb(0x1e, 0x4d1);

	/* setup RTC */
	CMOS_WRITE(RTC_SET, RTC_CONTROL);
	CMOS_WRITE(RTC_24H, RTC_CONTROL);

	/* ensure month, date, and week alarm fields are ignored */
	CMOS_WRITE(0, RTC_VALID);

	outb_p(0x7c, 0x72);
	outb_p(RTC_ALARM_DONT_CARE, 0x73);

	outb_p(0x7d, 0x72);
	outb_p(RTC_ALARM_DONT_CARE, 0x73);
}