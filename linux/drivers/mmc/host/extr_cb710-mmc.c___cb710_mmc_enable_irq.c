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
struct cb710_slot {int dummy; } ;

/* Variables and functions */
 unsigned short CB710_MMC_IE_IRQ_ENABLE ; 
 int /*<<< orphan*/  CB710_MMC_IRQ_ENABLE_PORT ; 
 unsigned short cb710_read_port_16 (struct cb710_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb710_write_port_16 (struct cb710_slot*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void __cb710_mmc_enable_irq(struct cb710_slot *slot,
	unsigned short enable, unsigned short mask)
{
	/* clear global IE
	 * - it gets set later if any interrupt sources are enabled */
	mask |= CB710_MMC_IE_IRQ_ENABLE;

	/* look like interrupt is fired whenever
	 * WORD[0x0C] & WORD[0x10] != 0;
	 * -> bit 15 port 0x0C seems to be global interrupt enable
	 */

	enable = (cb710_read_port_16(slot, CB710_MMC_IRQ_ENABLE_PORT)
		& ~mask) | enable;

	if (enable)
		enable |= CB710_MMC_IE_IRQ_ENABLE;

	cb710_write_port_16(slot, CB710_MMC_IRQ_ENABLE_PORT, enable);
}