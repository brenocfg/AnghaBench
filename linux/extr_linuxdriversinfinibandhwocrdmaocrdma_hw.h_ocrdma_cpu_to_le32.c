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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */

__attribute__((used)) static inline void ocrdma_cpu_to_le32(void *dst, u32 len)
{
#ifdef __BIG_ENDIAN
	int i = 0;
	u32 *src_ptr = dst;
	u32 *dst_ptr = dst;
	for (; i < (len / 4); i++)
		*(dst_ptr + i) = cpu_to_le32p(src_ptr + i);
#endif
}