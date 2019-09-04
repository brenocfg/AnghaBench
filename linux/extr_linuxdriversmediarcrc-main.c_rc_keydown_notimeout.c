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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rc_dev {int /*<<< orphan*/  keylock; } ;
typedef  enum rc_proto { ____Placeholder_rc_proto } rc_proto ;

/* Variables and functions */
 int /*<<< orphan*/  ir_do_keydown (struct rc_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_g_keycode_from_table (struct rc_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rc_keydown_notimeout(struct rc_dev *dev, enum rc_proto protocol,
			  u32 scancode, u8 toggle)
{
	unsigned long flags;
	u32 keycode = rc_g_keycode_from_table(dev, scancode);

	spin_lock_irqsave(&dev->keylock, flags);
	ir_do_keydown(dev, protocol, scancode, keycode, toggle);
	spin_unlock_irqrestore(&dev->keylock, flags);
}