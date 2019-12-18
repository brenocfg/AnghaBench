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
typedef  int u32 ;

/* Variables and functions */
 int cpu_to_le32p (int*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static inline void ocrdma_copy_cpu_to_le32(void *dst, void *src, u32 len)
{
#ifdef __BIG_ENDIAN
	int i = 0;
	u32 *src_ptr = src;
	u32 *dst_ptr = dst;
	for (; i < (len / sizeof(u32)); i++)
		*(dst_ptr + i) = cpu_to_le32p(src_ptr + i);
#else
	memcpy(dst, src, len);
#endif
}