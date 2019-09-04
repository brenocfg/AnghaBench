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
 int PAGE_SIZE ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static void
i915_gem_swizzle_page(struct page *page)
{
	char temp[64];
	char *vaddr;
	int i;

	vaddr = kmap(page);

	for (i = 0; i < PAGE_SIZE; i += 128) {
		memcpy(temp, &vaddr[i], 64);
		memcpy(&vaddr[i], &vaddr[i + 64], 64);
		memcpy(&vaddr[i + 64], temp, 64);
	}

	kunmap(page);
}