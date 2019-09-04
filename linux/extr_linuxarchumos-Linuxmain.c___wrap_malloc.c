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
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  UM_GFP_KERNEL ; 
 int UM_KERN_PAGE_SIZE ; 
 void* __real_malloc (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  kmalloc_ok ; 
 void* uml_kmalloc (int,int /*<<< orphan*/ ) ; 
 void* vmalloc (int) ; 

void *__wrap_malloc(int size)
{
	void *ret;

	if (!kmalloc_ok)
		return __real_malloc(size);
	else if (size <= UM_KERN_PAGE_SIZE)
		/* finding contiguous pages can be hard*/
		ret = uml_kmalloc(size, UM_GFP_KERNEL);
	else ret = vmalloc(size);

	/*
	 * glibc people insist that if malloc fails, errno should be
	 * set by malloc as well. So we do.
	 */
	if (ret == NULL)
		errno = ENOMEM;

	return ret;
}