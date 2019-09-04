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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  crc32_be (int /*<<< orphan*/ ,size_t*,int) ; 

__attribute__((used)) static inline u32 crc32_posix_end(u32 crc, size_t total_len)
{
	/* Extend with the length of the string. */
	while (total_len != 0) {
		u8 c = total_len & 0xff;

		crc = crc32_be(crc, &c, 1);
		total_len >>= 8;
	}

	return ~crc;
}