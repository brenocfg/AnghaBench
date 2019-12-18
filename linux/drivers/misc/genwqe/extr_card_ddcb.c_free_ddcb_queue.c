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
struct genwqe_dev {int dummy; } ;
struct ddcb_queue {int ddcb_max; unsigned long long ddcb_daddr; int /*<<< orphan*/ * ddcb_vaddr; int /*<<< orphan*/ * ddcb_req; } ;
struct ddcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __genwqe_free_consistent (struct genwqe_dev*,unsigned int,int /*<<< orphan*/ *,unsigned long long) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 unsigned int roundup (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_ddcb_queue(struct genwqe_dev *cd, struct ddcb_queue *queue)
{
	unsigned int queue_size;

	queue_size = roundup(queue->ddcb_max * sizeof(struct ddcb), PAGE_SIZE);

	kfree(queue->ddcb_req);
	queue->ddcb_req = NULL;

	if (queue->ddcb_vaddr) {
		__genwqe_free_consistent(cd, queue_size, queue->ddcb_vaddr,
					queue->ddcb_daddr);
		queue->ddcb_vaddr = NULL;
		queue->ddcb_daddr = 0ull;
	}
}