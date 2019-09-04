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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u8 rxe_get_key(void)
{
	static u32 key = 1;

	key = key << 1;

	key |= (0 != (key & 0x100)) ^ (0 != (key & 0x10))
		^ (0 != (key & 0x80)) ^ (0 != (key & 0x40));

	key &= 0xff;

	return key;
}