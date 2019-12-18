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
struct TYPE_2__ {int /*<<< orphan*/  sccb; struct sclp_buffer* callback_data; int /*<<< orphan*/  callback; int /*<<< orphan*/  status; int /*<<< orphan*/  command; } ;
struct sclp_buffer {scalar_t__ messages; void (* callback ) (struct sclp_buffer*,int) ;TYPE_1__ request; int /*<<< orphan*/  sccb; int /*<<< orphan*/ * current_line; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SCLP_CMDW_WRITE_EVENT_DATA ; 
 int /*<<< orphan*/  SCLP_REQ_FILLED ; 
 int sclp_add_request (TYPE_1__*) ; 
 int /*<<< orphan*/  sclp_finalize_mto (struct sclp_buffer*) ; 
 int /*<<< orphan*/  sclp_writedata_callback ; 

int
sclp_emit_buffer(struct sclp_buffer *buffer,
		 void (*callback)(struct sclp_buffer *, int))
{
	/* add current line if there is one */
	if (buffer->current_line != NULL)
		sclp_finalize_mto(buffer);

	/* Are there messages in the output buffer ? */
	if (buffer->messages == 0)
		return -EIO;

	buffer->request.command = SCLP_CMDW_WRITE_EVENT_DATA;
	buffer->request.status = SCLP_REQ_FILLED;
	buffer->request.callback = sclp_writedata_callback;
	buffer->request.callback_data = buffer;
	buffer->request.sccb = buffer->sccb;
	buffer->callback = callback;
	return sclp_add_request(&buffer->request);
}