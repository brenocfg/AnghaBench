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
struct zram {TYPE_1__* table; } ;
struct TYPE_2__ {unsigned long value; } ;

/* Variables and functions */
 unsigned long ZRAM_FLAG_SHIFT ; 

__attribute__((used)) static void zram_set_obj_size(struct zram *zram,
					u32 index, size_t size)
{
	unsigned long flags = zram->table[index].value >> ZRAM_FLAG_SHIFT;

	zram->table[index].value = (flags << ZRAM_FLAG_SHIFT) | size;
}