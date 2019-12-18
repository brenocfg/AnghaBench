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
struct page {int dummy; } ;

/* Variables and functions */
 unsigned long BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 

__attribute__((used)) static void siw_unmap_pages(struct page **pp, unsigned long kmap_mask)
{
	while (kmap_mask) {
		if (kmap_mask & BIT(0))
			kunmap(*pp);
		pp++;
		kmap_mask >>= 1;
	}
}