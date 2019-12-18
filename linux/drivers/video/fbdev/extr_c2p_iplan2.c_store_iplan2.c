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
 size_t* perm_c2p_16x8 ; 
 int /*<<< orphan*/  put_unaligned_be32 (int,void*) ; 

__attribute__((used)) static inline void store_iplan2(void *dst, u32 bpp, u32 d[4])
{
	int i;

	for (i = 0; i < bpp/2; i++, dst += 4)
		put_unaligned_be32(d[perm_c2p_16x8[i]], dst);
}