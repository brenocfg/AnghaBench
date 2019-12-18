#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct lpfc_queue {int hba_index; int entry_count; TYPE_1__* phba; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mbox; } ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static uint32_t
lpfc_sli4_mq_release(struct lpfc_queue *q)
{
	/* sanity check on queue memory */
	if (unlikely(!q))
		return 0;

	/* Clear the mailbox pointer for completion */
	q->phba->mbox = NULL;
	q->hba_index = ((q->hba_index + 1) % q->entry_count);
	return 1;
}