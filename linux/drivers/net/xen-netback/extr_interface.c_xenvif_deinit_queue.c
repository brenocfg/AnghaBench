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
struct xenvif_queue {int /*<<< orphan*/  mmap_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_PENDING_REQS ; 
 int /*<<< orphan*/  gnttab_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void xenvif_deinit_queue(struct xenvif_queue *queue)
{
	gnttab_free_pages(MAX_PENDING_REQS, queue->mmap_pages);
}