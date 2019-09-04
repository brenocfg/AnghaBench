#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sh_mtu2_channel {int index; TYPE_1__* mtu; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSTR ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long sh_mtu2_read (struct sh_mtu2_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_mtu2_write (struct sh_mtu2_channel*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void sh_mtu2_start_stop_ch(struct sh_mtu2_channel *ch, int start)
{
	unsigned long flags, value;

	/* start stop register shared by multiple timer channels */
	raw_spin_lock_irqsave(&ch->mtu->lock, flags);
	value = sh_mtu2_read(ch, TSTR);

	if (start)
		value |= 1 << ch->index;
	else
		value &= ~(1 << ch->index);

	sh_mtu2_write(ch, TSTR, value);
	raw_spin_unlock_irqrestore(&ch->mtu->lock, flags);
}