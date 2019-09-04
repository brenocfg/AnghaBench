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
struct gmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int _PAGE_ENTRIES ; 
 unsigned long _PAGE_INVALID ; 
 scalar_t__ _PAGE_SIZE ; 
 int /*<<< orphan*/  gmap_is_shadow (struct gmap*) ; 

__attribute__((used)) static void __gmap_unshadow_pgt(struct gmap *sg, unsigned long raddr,
				unsigned long *pgt)
{
	int i;

	BUG_ON(!gmap_is_shadow(sg));
	for (i = 0; i < _PAGE_ENTRIES; i++, raddr += _PAGE_SIZE)
		pgt[i] = _PAGE_INVALID;
}