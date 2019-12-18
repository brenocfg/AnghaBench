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
struct host1x_cdma {int running; int torndown; int /*<<< orphan*/  push_buffer; int /*<<< orphan*/  event; int /*<<< orphan*/  sync_queue; int /*<<< orphan*/  complete; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDMA_EVENT_NONE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int host1x_pushbuffer_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int host1x_cdma_init(struct host1x_cdma *cdma)
{
	int err;

	mutex_init(&cdma->lock);
	init_completion(&cdma->complete);

	INIT_LIST_HEAD(&cdma->sync_queue);

	cdma->event = CDMA_EVENT_NONE;
	cdma->running = false;
	cdma->torndown = false;

	err = host1x_pushbuffer_init(&cdma->push_buffer);
	if (err)
		return err;

	return 0;
}