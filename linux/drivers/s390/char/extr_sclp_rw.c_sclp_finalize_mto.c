#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sclp_buffer {struct msg_buf* current_msg; scalar_t__ current_length; int /*<<< orphan*/ * current_line; int /*<<< orphan*/  char_sum; int /*<<< orphan*/  messages; struct sccb_header* sccb; } ;
struct sccb_header {int /*<<< orphan*/  length; } ;
struct TYPE_8__ {scalar_t__ length; } ;
struct TYPE_6__ {int /*<<< orphan*/  length; } ;
struct TYPE_5__ {int /*<<< orphan*/  length; } ;
struct TYPE_7__ {TYPE_2__ mto; TYPE_1__ header; } ;
struct msg_buf {TYPE_4__ header; TYPE_3__ mdb; } ;

/* Variables and functions */

__attribute__((used)) static void
sclp_finalize_mto(struct sclp_buffer *buffer)
{
	struct sccb_header *sccb;
	struct msg_buf *msg;

	/*
	 * update values of sizes
	 * (SCCB, Event(Message) Buffer, Message Data Block)
	 */
	sccb = buffer->sccb;
	msg = buffer->current_msg;
	msg->header.length += buffer->current_length;
	msg->mdb.header.length += buffer->current_length;
	msg->mdb.mto.length += buffer->current_length;
	sccb->length += msg->header.length;

	/*
	 * count number of buffered messages (= number of Message Text
	 * Objects) and number of buffered characters
	 * for the SCCB currently used for buffering and at all
	 */
	buffer->messages++;
	buffer->char_sum += buffer->current_length;

	buffer->current_line = NULL;
	buffer->current_length = 0;
	buffer->current_msg = NULL;
}