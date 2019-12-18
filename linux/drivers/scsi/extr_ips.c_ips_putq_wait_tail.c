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
struct scsi_cmnd {char* host_scribble; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; struct scsi_cmnd* head; struct scsi_cmnd* tail; } ;
typedef  TYPE_1__ ips_wait_queue_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 

__attribute__((used)) static void ips_putq_wait_tail(ips_wait_queue_entry_t *queue, struct scsi_cmnd *item)
{
	METHOD_TRACE("ips_putq_wait_tail", 1);

	if (!item)
		return;

	item->host_scribble = NULL;

	if (queue->tail)
		queue->tail->host_scribble = (char *) item;

	queue->tail = item;

	if (!queue->head)
		queue->head = item;

	queue->count++;
}