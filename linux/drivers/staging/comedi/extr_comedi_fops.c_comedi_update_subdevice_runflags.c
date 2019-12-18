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
struct comedi_subdevice {int /*<<< orphan*/  spin_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __comedi_clear_subdevice_runflags (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  __comedi_set_subdevice_runflags (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void comedi_update_subdevice_runflags(struct comedi_subdevice *s,
					     unsigned int mask,
					     unsigned int bits)
{
	unsigned long flags;

	spin_lock_irqsave(&s->spin_lock, flags);
	__comedi_clear_subdevice_runflags(s, mask);
	__comedi_set_subdevice_runflags(s, bits & mask);
	spin_unlock_irqrestore(&s->spin_lock, flags);
}