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
 int PBLK_KMALLOC_META ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  vfree (void*) ; 

__attribute__((used)) static inline void pblk_mfree(void *ptr, int type)
{
	if (type == PBLK_KMALLOC_META)
		kfree(ptr);
	else
		vfree(ptr);
}