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
typedef  size_t u16 ;
struct xenvif_queue {int /*<<< orphan*/ * mmap_pages; } ;

/* Variables and functions */
 unsigned long page_to_pfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long idx_to_pfn(struct xenvif_queue *queue,
				       u16 idx)
{
	return page_to_pfn(queue->mmap_pages[idx]);
}