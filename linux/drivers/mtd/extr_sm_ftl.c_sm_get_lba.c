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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int hweight16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sm_get_lba(uint8_t *lba)
{
	/* check fixed bits */
	if ((lba[0] & 0xF8) != 0x10)
		return -2;

	/* check parity - endianness doesn't matter */
	if (hweight16(*(uint16_t *)lba) & 1)
		return -2;

	return (lba[1] >> 1) | ((lba[0] & 0x07) << 7);
}