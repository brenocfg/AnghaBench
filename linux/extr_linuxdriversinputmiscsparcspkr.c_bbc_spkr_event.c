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
struct bbc_beep_info {scalar_t__ regs; } ;
struct TYPE_4__ {struct bbc_beep_info bbc; } ;
struct sparcspkr_state {int /*<<< orphan*/  lock; TYPE_2__ u; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct input_dev {TYPE_1__ dev; } ;

/* Variables and functions */
 unsigned int EV_SND ; 
#define  SND_BELL 129 
#define  SND_TONE 128 
 unsigned int bbc_count_to_reg (struct bbc_beep_info*,unsigned int) ; 
 struct sparcspkr_state* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbus_writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int bbc_spkr_event(struct input_dev *dev, unsigned int type, unsigned int code, int value)
{
	struct sparcspkr_state *state = dev_get_drvdata(dev->dev.parent);
	struct bbc_beep_info *info = &state->u.bbc;
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

	count = bbc_count_to_reg(info, count);

	spin_lock_irqsave(&state->lock, flags);

	if (count) {
		sbus_writeb(0x01,                 info->regs + 0);
		sbus_writeb(0x00,                 info->regs + 2);
		sbus_writeb((count >> 16) & 0xff, info->regs + 3);
		sbus_writeb((count >>  8) & 0xff, info->regs + 4);
		sbus_writeb(0x00,                 info->regs + 5);
	} else {
		sbus_writeb(0x00,                 info->regs + 0);
	}

	spin_unlock_irqrestore(&state->lock, flags);

	return 0;
}