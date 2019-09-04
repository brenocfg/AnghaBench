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
struct input_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int EV_SND ; 
 int PIT_TICK_RATE ; 
#define  SND_BELL 129 
#define  SND_TONE 128 
 int /*<<< orphan*/  i8253_lock ; 
 int inb_p (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  outb_p (int,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pcspkr_event(struct input_dev *dev, unsigned int type,
			unsigned int code, int value)
{
	unsigned int count = 0;
	unsigned long flags;

	if (type != EV_SND)
		return -EINVAL;

	switch (code) {
	case SND_BELL:
		if (value)
			value = 1000;
	case SND_TONE:
		break;
	default:
		return -EINVAL;
	}

	if (value > 20 && value < 32767)
		count = PIT_TICK_RATE / value;

	raw_spin_lock_irqsave(&i8253_lock, flags);

	if (count) {
		/* set command for counter 2, 2 byte write */
		outb_p(0xB6, 0x43);
		/* select desired HZ */
		outb_p(count & 0xff, 0x42);
		outb((count >> 8) & 0xff, 0x42);
		/* enable counter 2 */
		outb_p(inb_p(0x61) | 3, 0x61);
	} else {
		/* disable counter 2 */
		outb(inb_p(0x61) & 0xFC, 0x61);
	}

	raw_spin_unlock_irqrestore(&i8253_lock, flags);

	return 0;
}