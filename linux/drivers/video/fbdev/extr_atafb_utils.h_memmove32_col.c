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

__attribute__((used)) static inline void memmove32_col(void *dst, void *src, u32 mask, u32 h, u32 bytes)
{
	u32 *s, *d, v;

        s = src;
        d = dst;
        do {
                v = (*s++ & mask) | (*d  & ~mask);
                *d++ = v;
#if BPL > 2
                v = (*s++ & mask) | (*d  & ~mask);
                *d++ = v;
#endif
#if BPL > 4
                v = (*s++ & mask) | (*d  & ~mask);
                *d++ = v;
                v = (*s++ & mask) | (*d  & ~mask);
                *d++ = v;
#endif
                d = (u32 *)((u8 *)d + bytes);
                s = (u32 *)((u8 *)s + bytes);
        } while (--h);
}