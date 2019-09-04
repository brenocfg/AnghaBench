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
 int /*<<< orphan*/  cmd640_lock ; 
 int inb (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pci_conf2(void)
{
	unsigned long flags;

	spin_lock_irqsave(&cmd640_lock, flags);
	outb(0x00, 0xCFB);
	outb(0x00, 0xCF8);
	outb(0x00, 0xCFA);
	if (inb(0xCF8) == 0x00 && inb(0xCF8) == 0x00) {
		spin_unlock_irqrestore(&cmd640_lock, flags);
		return 1;
	}
	spin_unlock_irqrestore(&cmd640_lock, flags);
	return 0;
}