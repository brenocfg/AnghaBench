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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static const u8 *coda_find_nal_header(const u8 *buf, const u8 *end)
{
	u32 val = 0xffffffff;

	do {
		val = val << 8 | *buf++;
		if (buf >= end)
			return NULL;
	} while (val != 0x00000001);

	return buf;
}