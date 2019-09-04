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
typedef  size_t u64 ;
struct pvrdma_page_dir {void** pages; } ;

/* Variables and functions */
 size_t PAGE_SIZE ; 

__attribute__((used)) static inline void *pvrdma_page_dir_get_ptr(struct pvrdma_page_dir *pdir,
					    u64 offset)
{
	return pdir->pages[offset / PAGE_SIZE] + (offset % PAGE_SIZE);
}