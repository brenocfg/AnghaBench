#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct grover_beep_info {scalar_t__ enable_reg; scalar_t__ freq_regs; } ;
struct TYPE_4__ {struct grover_beep_info grover; } ;
struct sparcspkr_state {int /*<<< orphan*/  lock; TYPE_2__ u; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct input_dev {TYPE_1__ dev; } ;

/* Variables and functions */
 unsigned int EV_SND ; 
#define  SND_BELL 129 
#define  SND_TONE 128 
 struct sparcspkr_state* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int sbus_readb (scalar_t__) ; 
 int /*<<< orphan*/  sbus_writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int grover_spkr_event(struct input_dev *dev, unsigned int type, unsigned int code, int value)
{
	struct sparcspkr_state *state = dev_get_drvdata(dev->dev.parent);
	struct grover_beep_info *info = &state->u.grover;
	unsigned int count = 0;
	unsigned long flags;

	if (type != EV_SND)
		return -1;

	switch (code) {
		case SND_BELL: if (value) value = 1000;
		case SND_TONE: break;
		default: return -1;
	}

	if (value > 20 && value < 32767)
		count = 1193182 / value;

	spin_lock_irqsave(&state->lock, flags);

	if (count) {
		/* enable counter 2 */
		sbus_writeb(sbus_readb(info->enable_reg) | 3, info->enable_reg);
		/* set command for counter 2, 2 byte write */
		sbus_writeb(0xB6, info->freq_regs + 1);
		/* select desired HZ */
		sbus_writeb(count & 0xff, info->freq_regs + 0);
		sbus_writeb((count >> 8) & 0xff, info->freq_regs + 0);
	} else {
		/* disable counter 2 */
		sbus_writeb(sbus_readb(info->enable_reg) & 0xFC, info->enable_reg);
	}

	spin_unlock_irqrestore(&state->lock, flags);

	return 0;
}