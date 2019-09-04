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
struct cec_data {int completed; int /*<<< orphan*/  msg; scalar_t__ fh; int /*<<< orphan*/  c; scalar_t__ blocking; int /*<<< orphan*/  xfer_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  cec_queue_msg_fh (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cec_data*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cec_data_completed(struct cec_data *data)
{
	/*
	 * Delete this transmit from the filehandle's xfer_list since
	 * we're done with it.
	 *
	 * Note that if the filehandle is closed before this transmit
	 * finished, then the release() function will set data->fh to NULL.
	 * Without that we would be referring to a closed filehandle.
	 */
	if (data->fh)
		list_del(&data->xfer_list);

	if (data->blocking) {
		/*
		 * Someone is blocking so mark the message as completed
		 * and call complete.
		 */
		data->completed = true;
		complete(&data->c);
	} else {
		/*
		 * No blocking, so just queue the message if needed and
		 * free the memory.
		 */
		if (data->fh)
			cec_queue_msg_fh(data->fh, &data->msg);
		kfree(data);
	}
}