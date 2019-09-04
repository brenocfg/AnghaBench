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
#define  IND_DESTINATION 130 
 unsigned long IND_DONE ; 
 unsigned long IND_FLAGS ; 
#define  IND_INDIRECTION 129 
#define  IND_SOURCE 128 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 void* __va (unsigned long) ; 
 int /*<<< orphan*/  copy_page (void*,void*) ; 

__attribute__((used)) static void copy_segments(unsigned long ind)
{
	unsigned long entry;
	unsigned long *ptr;
	void *dest;
	void *addr;

	/*
	 * We rely on kexec_load to create a lists that properly
	 * initializes these pointers before they are used.
	 * We will still crash if the list is wrong, but at least
	 * the compiler will be quiet.
	 */
	ptr = NULL;
	dest = NULL;

	for (entry = ind; !(entry & IND_DONE); entry = *ptr++) {
		addr = __va(entry & PAGE_MASK);

		switch (entry & IND_FLAGS) {
		case IND_DESTINATION:
			dest = addr;
			break;
		case IND_INDIRECTION:
			ptr = addr;
			break;
		case IND_SOURCE:
			copy_page(dest, addr);
			dest += PAGE_SIZE;
		}
	}
}