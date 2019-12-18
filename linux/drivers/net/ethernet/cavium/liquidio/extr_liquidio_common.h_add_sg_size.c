#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  void* u16 ;
struct TYPE_2__ {void** size; } ;
struct octeon_sg_entry {TYPE_1__ u; } ;

/* Variables and functions */

__attribute__((used)) static inline void add_sg_size(struct octeon_sg_entry *sg_entry,
			       u16 size,
			       u32 pos)
{
#ifdef __BIG_ENDIAN_BITFIELD
	sg_entry->u.size[pos] = size;
#else
	sg_entry->u.size[3 - pos] = size;
#endif
}