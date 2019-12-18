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

__attribute__((used)) static void pb_sample_cpy(u8 *dst, const u8 *src, u32 len, bool is_s32)
{
	static const unsigned map[8] = { 0, 1, 5, 4, 2, 3, 6, 7 };
	unsigned idx = 0;

	while (len >= (is_s32 ? 4 : 2)) {
		unsigned offset = map[idx] * 4;
		u8 *out = dst + offset;

		*out++ = 0;
		if (is_s32) {
			src++;
			*out++ = *src++;
		} else {
			*out++ = 0;
		}
		*out++ = *src++;
		*out = *src++;
		len -= is_s32 ? 4 : 2;
		idx++;
	}
}