#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rc_map_table {int dummy; } ;
struct rc_map {unsigned int len; unsigned int size; TYPE_1__* scan; } ;
struct rc_dev {int scancode_mask; } ;
struct TYPE_3__ {unsigned int scancode; int /*<<< orphan*/  keycode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  KEY_RESERVED ; 
 scalar_t__ ir_resize_table (struct rc_dev*,struct rc_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (TYPE_1__*,TYPE_1__*,unsigned int) ; 

__attribute__((used)) static unsigned int ir_establish_scancode(struct rc_dev *dev,
					  struct rc_map *rc_map,
					  unsigned int scancode,
					  bool resize)
{
	unsigned int i;

	/*
	 * Unfortunately, some hardware-based IR decoders don't provide
	 * all bits for the complete IR code. In general, they provide only
	 * the command part of the IR code. Yet, as it is possible to replace
	 * the provided IR with another one, it is needed to allow loading
	 * IR tables from other remotes. So, we support specifying a mask to
	 * indicate the valid bits of the scancodes.
	 */
	if (dev->scancode_mask)
		scancode &= dev->scancode_mask;

	/* First check if we already have a mapping for this ir command */
	for (i = 0; i < rc_map->len; i++) {
		if (rc_map->scan[i].scancode == scancode)
			return i;

		/* Keytable is sorted from lowest to highest scancode */
		if (rc_map->scan[i].scancode >= scancode)
			break;
	}

	/* No previous mapping found, we might need to grow the table */
	if (rc_map->size == rc_map->len) {
		if (!resize || ir_resize_table(dev, rc_map, GFP_ATOMIC))
			return -1U;
	}

	/* i is the proper index to insert our new keycode */
	if (i < rc_map->len)
		memmove(&rc_map->scan[i + 1], &rc_map->scan[i],
			(rc_map->len - i) * sizeof(struct rc_map_table));
	rc_map->scan[i].scancode = scancode;
	rc_map->scan[i].keycode = KEY_RESERVED;
	rc_map->len++;

	return i;
}