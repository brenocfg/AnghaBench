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
 int /*<<< orphan*/  memcpy (void*,void const*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 

__attribute__((used)) static inline void
__copy_xstate_to_kernel(void *kbuf, const void *data,
			unsigned int offset, unsigned int size, unsigned int size_total)
{
	if (offset < size_total) {
		unsigned int copy = min(size, size_total - offset);

		memcpy(kbuf + offset, data, copy);
	}
}