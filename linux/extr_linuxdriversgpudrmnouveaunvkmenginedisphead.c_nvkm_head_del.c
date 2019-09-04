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
struct nvkm_head {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEAD_DBG (struct nvkm_head*,char*) ; 
 int /*<<< orphan*/  kfree (struct nvkm_head*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void
nvkm_head_del(struct nvkm_head **phead)
{
	struct nvkm_head *head = *phead;
	if (head) {
		HEAD_DBG(head, "dtor");
		list_del(&head->head);
		kfree(*phead);
		*phead = NULL;
	}
}