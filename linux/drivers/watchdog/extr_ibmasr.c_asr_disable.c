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
 scalar_t__ ASMTYPE_TOPAZ ; 
 unsigned char TOPAZ_ASR_DISABLE ; 
 unsigned char TOPAZ_ASR_TOGGLE ; 
 unsigned char asr_disable_mask ; 
 int /*<<< orphan*/  asr_lock ; 
 int /*<<< orphan*/  asr_read_addr ; 
 unsigned char asr_toggle_mask ; 
 scalar_t__ asr_type ; 
 int /*<<< orphan*/  asr_write_addr ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void asr_disable(void)
{
	unsigned char reg;

	spin_lock(&asr_lock);
	reg = inb(asr_read_addr);

	if (asr_type == ASMTYPE_TOPAZ)
		/* asr_write_addr == asr_read_addr */
		outb(reg | TOPAZ_ASR_TOGGLE | TOPAZ_ASR_DISABLE,
		     asr_read_addr);
	else {
		outb(reg | asr_toggle_mask, asr_write_addr);
		reg = inb(asr_read_addr);

		outb(reg | asr_disable_mask, asr_write_addr);
	}
	reg = inb(asr_read_addr);
	spin_unlock(&asr_lock);
}