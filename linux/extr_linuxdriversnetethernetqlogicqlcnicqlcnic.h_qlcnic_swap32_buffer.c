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

__attribute__((used)) static inline void qlcnic_swap32_buffer(u32 *buffer, int count)
{
#if defined(__BIG_ENDIAN)
	u32 *tmp = buffer;
	int i;

	for (i = 0; i < count; i++) {
		*tmp = swab32(*tmp);
		tmp++;
	}
#endif
}