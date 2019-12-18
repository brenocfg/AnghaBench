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
 int KEY_MASK ; 
 int TWO_PACKETS_MASK ; 

__attribute__((used)) static int get_key(int data)
{
	/*
	 * The key is coded accross bits 2..9:
	 *
	 * 0x00 or 0x01 (        )	key:  0		-> KEY_RESERVED
	 * 0x02 or 0x03 (  menu  )	key:  1		-> KEY_MENU
	 * 0x04 or 0x05 (   >"   )	key:  2		-> KEY_PLAYPAUSE
	 * 0x06 or 0x07 (   >>   )	key:  3		-> KEY_FORWARD
	 * 0x08 or 0x09 (   <<   )	key:  4		-> KEY_BACK
	 * 0x0a or 0x0b (    +   )	key:  5		-> KEY_VOLUMEUP
	 * 0x0c or 0x0d (    -   )	key:  6		-> KEY_VOLUMEDOWN
	 * 0x0e or 0x0f (        )	key:  7		-> KEY_RESERVED
	 * 0x50 or 0x51 (        )	key:  8		-> KEY_RESERVED
	 * 0x52 or 0x53 (        )	key:  9		-> KEY_RESERVED
	 * 0x54 or 0x55 (        )	key: 10		-> KEY_RESERVED
	 * 0x56 or 0x57 (        )	key: 11		-> KEY_RESERVED
	 * 0x58 or 0x59 (        )	key: 12		-> KEY_RESERVED
	 * 0x5a or 0x5b (        )	key: 13		-> KEY_RESERVED
	 * 0x5c or 0x5d ( middle )	key: 14		-> KEY_ENTER
	 * 0x5e or 0x5f (   >"   )	key: 15		-> KEY_PLAYPAUSE
	 *
	 * Packets starting with 0x5 are part of a two-packets message,
	 * we notify the caller by sending a negative value.
	 */
	int key = (data >> 1) & KEY_MASK;

	if ((data & TWO_PACKETS_MASK))
		/* Part of a 2 packets-command */
		key = -key;

	return key;
}