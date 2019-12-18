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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  crc32_le (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sja1105_unpack (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

u32 sja1105_crc32(const void *buf, size_t len)
{
	unsigned int i;
	u64 word;
	u32 crc;

	/* seed */
	crc = ~0;
	for (i = 0; i < len; i += 4) {
		sja1105_unpack((void *)buf + i, &word, 31, 0, 4);
		crc = crc32_le(crc, (u8 *)&word, 4);
	}
	return ~crc;
}