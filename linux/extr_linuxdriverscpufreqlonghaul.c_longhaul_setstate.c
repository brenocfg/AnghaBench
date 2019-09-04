#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct cpufreq_policy {int dummy; } ;
struct cpufreq_freqs {int new; void* old; } ;
struct TYPE_8__ {int /*<<< orphan*/  address; } ;
struct TYPE_7__ {unsigned int driver_data; } ;
struct TYPE_5__ {scalar_t__ bm_control; } ;
struct TYPE_6__ {TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BITREG_ARB_DISABLE ; 
 int /*<<< orphan*/  ACPI_BITREG_BUS_MASTER_RLD ; 
 int EBUSY ; 
 int EINVAL ; 
#define  TYPE_LONGHAUL_V1 130 
#define  TYPE_LONGHAUL_V2 129 
#define  TYPE_POWERSAVER 128 
 int USE_ACPI_C3 ; 
 int USE_NORTHBRIDGE ; 
 scalar_t__ acpi_regs_addr ; 
 int /*<<< orphan*/  acpi_write_bit_register (int /*<<< orphan*/ ,int) ; 
 void* calc_speed (int) ; 
 scalar_t__ can_scale_voltage ; 
 TYPE_4__* cx ; 
 int /*<<< orphan*/  do_longhaul1 (unsigned int) ; 
 int /*<<< orphan*/  do_powersaver (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  fsb ; 
 int highest_speed ; 
 unsigned int inb (int) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int longhaul_flags ; 
 int longhaul_get_cpu_mult () ; 
 unsigned int longhaul_index ; 
 TYPE_3__* longhaul_table ; 
 int longhaul_version ; 
 int lowest_speed ; 
 int /*<<< orphan*/  msleep (int) ; 
 int* mults ; 
 int /*<<< orphan*/  outb (unsigned int,int) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 TYPE_2__* pr ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  print_speed (int) ; 
 int revid_errata ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int longhaul_setstate(struct cpufreq_policy *policy,
		unsigned int table_index)
{
	unsigned int mults_index;
	int speed, mult;
	struct cpufreq_freqs freqs;
	unsigned long flags;
	unsigned int pic1_mask, pic2_mask;
	u16 bm_status = 0;
	u32 bm_timeout = 1000;
	unsigned int dir = 0;

	mults_index = longhaul_table[table_index].driver_data;
	/* Safety precautions */
	mult = mults[mults_index & 0x1f];
	if (mult == -1)
		return -EINVAL;

	speed = calc_speed(mult);
	if ((speed > highest_speed) || (speed < lowest_speed))
		return -EINVAL;

	/* Voltage transition before frequency transition? */
	if (can_scale_voltage && longhaul_index < table_index)
		dir = 1;

	freqs.old = calc_speed(longhaul_get_cpu_mult());
	freqs.new = speed;

	pr_debug("Setting to FSB:%dMHz Mult:%d.%dx (%s)\n",
			fsb, mult/10, mult%10, print_speed(speed/1000));
retry_loop:
	preempt_disable();
	local_irq_save(flags);

	pic2_mask = inb(0xA1);
	pic1_mask = inb(0x21);	/* works on C3. save mask. */
	outb(0xFF, 0xA1);	/* Overkill */
	outb(0xFE, 0x21);	/* TMR0 only */

	/* Wait while PCI bus is busy. */
	if (acpi_regs_addr && (longhaul_flags & USE_NORTHBRIDGE
	    || ((pr != NULL) && pr->flags.bm_control))) {
		bm_status = inw(acpi_regs_addr);
		bm_status &= 1 << 4;
		while (bm_status && bm_timeout) {
			outw(1 << 4, acpi_regs_addr);
			bm_timeout--;
			bm_status = inw(acpi_regs_addr);
			bm_status &= 1 << 4;
		}
	}

	if (longhaul_flags & USE_NORTHBRIDGE) {
		/* Disable AGP and PCI arbiters */
		outb(3, 0x22);
	} else if ((pr != NULL) && pr->flags.bm_control) {
		/* Disable bus master arbitration */
		acpi_write_bit_register(ACPI_BITREG_ARB_DISABLE, 1);
	}
	switch (longhaul_version) {

	/*
	 * Longhaul v1. (Samuel[C5A] and Samuel2 stepping 0[C5B])
	 * Software controlled multipliers only.
	 */
	case TYPE_LONGHAUL_V1:
		do_longhaul1(mults_index);
		break;

	/*
	 * Longhaul v2 appears in Samuel2 Steppings 1->7 [C5B] and Ezra [C5C]
	 *
	 * Longhaul v3 (aka Powersaver). (Ezra-T [C5M] & Nehemiah [C5N])
	 * Nehemiah can do FSB scaling too, but this has never been proven
	 * to work in practice.
	 */
	case TYPE_LONGHAUL_V2:
	case TYPE_POWERSAVER:
		if (longhaul_flags & USE_ACPI_C3) {
			/* Don't allow wakeup */
			acpi_write_bit_register(ACPI_BITREG_BUS_MASTER_RLD, 0);
			do_powersaver(cx->address, mults_index, dir);
		} else {
			do_powersaver(0, mults_index, dir);
		}
		break;
	}

	if (longhaul_flags & USE_NORTHBRIDGE) {
		/* Enable arbiters */
		outb(0, 0x22);
	} else if ((pr != NULL) && pr->flags.bm_control) {
		/* Enable bus master arbitration */
		acpi_write_bit_register(ACPI_BITREG_ARB_DISABLE, 0);
	}
	outb(pic2_mask, 0xA1);	/* restore mask */
	outb(pic1_mask, 0x21);

	local_irq_restore(flags);
	preempt_enable();

	freqs.new = calc_speed(longhaul_get_cpu_mult());
	/* Check if requested frequency is set. */
	if (unlikely(freqs.new != speed)) {
		pr_info("Failed to set requested frequency!\n");
		/* Revision ID = 1 but processor is expecting revision key
		 * equal to 0. Jumpers at the bottom of processor will change
		 * multiplier and FSB, but will not change bits in Longhaul
		 * MSR nor enable voltage scaling. */
		if (!revid_errata) {
			pr_info("Enabling \"Ignore Revision ID\" option\n");
			revid_errata = 1;
			msleep(200);
			goto retry_loop;
		}
		/* Why ACPI C3 sometimes doesn't work is a mystery for me.
		 * But it does happen. Processor is entering ACPI C3 state,
		 * but it doesn't change frequency. I tried poking various
		 * bits in northbridge registers, but without success. */
		if (longhaul_flags & USE_ACPI_C3) {
			pr_info("Disabling ACPI C3 support\n");
			longhaul_flags &= ~USE_ACPI_C3;
			if (revid_errata) {
				pr_info("Disabling \"Ignore Revision ID\" option\n");
				revid_errata = 0;
			}
			msleep(200);
			goto retry_loop;
		}
		/* This shouldn't happen. Longhaul ver. 2 was reported not
		 * working on processors without voltage scaling, but with
		 * RevID = 1. RevID errata will make things right. Just
		 * to be 100% sure. */
		if (longhaul_version == TYPE_LONGHAUL_V2) {
			pr_info("Switching to Longhaul ver. 1\n");
			longhaul_version = TYPE_LONGHAUL_V1;
			msleep(200);
			goto retry_loop;
		}
	}

	if (!bm_timeout) {
		pr_info("Warning: Timeout while waiting for idle PCI bus\n");
		return -EBUSY;
	}

	return 0;
}