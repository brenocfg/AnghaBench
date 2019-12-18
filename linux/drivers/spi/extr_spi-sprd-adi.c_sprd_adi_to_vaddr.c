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
typedef  unsigned long u32 ;
struct sprd_adi {unsigned long slave_pbase; unsigned long slave_vbase; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long sprd_adi_to_vaddr(struct sprd_adi *sadi, u32 paddr)
{
	return (paddr - sadi->slave_pbase + sadi->slave_vbase);
}