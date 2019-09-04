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
typedef  int uint32_t ;
struct cs5535_mfgpt_timer {int nr; } ;

/* Variables and functions */
 int CONFIG_CS5535_MFGPT_DEFAULT_IRQ ; 
 int EIO ; 
 int MFGPT_CMP1 ; 
 int /*<<< orphan*/  MFGPT_EVENT_IRQ ; 
 int /*<<< orphan*/  MSR_PIC_IRQM_LPC ; 
 int /*<<< orphan*/  MSR_PIC_ZSEL_LOW ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ cs5535_mfgpt_toggle_event (struct cs5535_mfgpt_timer*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int,int) ; 

int cs5535_mfgpt_set_irq(struct cs5535_mfgpt_timer *timer, int cmp, int *irq,
		int enable)
{
	uint32_t zsel, lpc, dummy;
	int shift;

	if (!timer) {
		WARN_ON(1);
		return -EIO;
	}

	/*
	 * Unfortunately, MFGPTs come in pairs sharing their IRQ lines. If VSA
	 * is using the same CMP of the timer's Siamese twin, the IRQ is set to
	 * 2, and we mustn't use nor change it.
	 * XXX: Likewise, 2 Linux drivers might clash if the 2nd overwrites the
	 * IRQ of the 1st. This can only happen if forcing an IRQ, calling this
	 * with *irq==0 is safe. Currently there _are_ no 2 drivers.
	 */
	rdmsr(MSR_PIC_ZSEL_LOW, zsel, dummy);
	shift = ((cmp == MFGPT_CMP1 ? 0 : 4) + timer->nr % 4) * 4;
	if (((zsel >> shift) & 0xF) == 2)
		return -EIO;

	/* Choose IRQ: if none supplied, keep IRQ already set or use default */
	if (!*irq)
		*irq = (zsel >> shift) & 0xF;
	if (!*irq)
		*irq = CONFIG_CS5535_MFGPT_DEFAULT_IRQ;

	/* Can't use IRQ if it's 0 (=disabled), 2, or routed to LPC */
	if (*irq < 1 || *irq == 2 || *irq > 15)
		return -EIO;
	rdmsr(MSR_PIC_IRQM_LPC, lpc, dummy);
	if (lpc & (1 << *irq))
		return -EIO;

	/* All chosen and checked - go for it */
	if (cs5535_mfgpt_toggle_event(timer, cmp, MFGPT_EVENT_IRQ, enable))
		return -EIO;
	if (enable) {
		zsel = (zsel & ~(0xF << shift)) | (*irq << shift);
		wrmsr(MSR_PIC_ZSEL_LOW, zsel, dummy);
	}

	return 0;
}