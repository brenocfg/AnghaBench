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
typedef  int u8 ;
typedef  int /*<<< orphan*/  keyboard_ids ;

/* Variables and functions */
 int /*<<< orphan*/ * memchr (int const*,int,int) ; 

bool ps2_is_keyboard_id(u8 id_byte)
{
	static const u8 keyboard_ids[] = {
		0xab,	/* Regular keyboards		*/
		0xac,	/* NCD Sun keyboard		*/
		0x2b,	/* Trust keyboard, translated	*/
		0x5d,	/* Trust keyboard		*/
		0x60,	/* NMB SGI keyboard, translated */
		0x47,	/* NMB SGI keyboard		*/
	};

	return memchr(keyboard_ids, id_byte, sizeof(keyboard_ids)) != NULL;
}