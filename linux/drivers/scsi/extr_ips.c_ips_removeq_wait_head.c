#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int /*<<< orphan*/ * host_scribble; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; struct scsi_cmnd* tail; struct scsi_cmnd* head; } ;
typedef  TYPE_1__ ips_wait_queue_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 

__attribute__((used)) static struct scsi_cmnd *ips_removeq_wait_head(ips_wait_queue_entry_t *queue)
{
	struct scsi_cmnd *item;

	METHOD_TRACE("ips_removeq_wait_head", 1);

	item = queue->head;

	if (!item) {
		return (NULL);
	}

	queue->head = (struct scsi_cmnd *) item->host_scribble;
	item->host_scribble = NULL;

	if (queue->tail == item)
		queue->tail = NULL;

	queue->count--;

	return (item);
}