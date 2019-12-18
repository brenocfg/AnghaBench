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
typedef  unsigned int u32 ;
struct rc_map {unsigned int len; int /*<<< orphan*/  lock; TYPE_1__* scan; } ;
struct rc_dev {int /*<<< orphan*/  device_name; int /*<<< orphan*/  dev; struct rc_map rc_map; } ;
struct TYPE_2__ {unsigned int keycode; } ;

/* Variables and functions */
 unsigned int KEY_RESERVED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 unsigned int ir_lookup_by_scancode (struct rc_map*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

u32 rc_g_keycode_from_table(struct rc_dev *dev, u32 scancode)
{
	struct rc_map *rc_map = &dev->rc_map;
	unsigned int keycode;
	unsigned int index;
	unsigned long flags;

	spin_lock_irqsave(&rc_map->lock, flags);

	index = ir_lookup_by_scancode(rc_map, scancode);
	keycode = index < rc_map->len ?
			rc_map->scan[index].keycode : KEY_RESERVED;

	spin_unlock_irqrestore(&rc_map->lock, flags);

	if (keycode != KEY_RESERVED)
		dev_dbg(&dev->dev, "%s: scancode 0x%04x keycode 0x%02x\n",
			dev->device_name, scancode, keycode);

	return keycode;
}