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
struct alloc_info {unsigned long size; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,unsigned long) ; 
 struct alloc_info* simple_find_entry (void*) ; 
 int /*<<< orphan*/  simple_free (void*) ; 
 void* simple_malloc (unsigned long) ; 

__attribute__((used)) static void *simple_realloc(void *ptr, unsigned long size)
{
	struct alloc_info *p;
	void *new;

	if (size == 0) {
		simple_free(ptr);
		return NULL;
	}

	if (ptr == NULL)
		return simple_malloc(size);

	p = simple_find_entry(ptr);
	if (p == NULL) /* ptr not from simple_malloc/simple_realloc */
		return NULL;
	if (size <= p->size) /* fits in current block */
		return ptr;

	new = simple_malloc(size);
	memcpy(new, ptr, p->size);
	simple_free(ptr);
	return new;
}