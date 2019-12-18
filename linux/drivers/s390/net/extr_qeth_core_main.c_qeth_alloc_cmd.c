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
struct qeth_cmd_buffer {long timeout; unsigned int length; struct qeth_channel* channel; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; int /*<<< orphan*/  done; void* data; } ;
struct qeth_channel {int dummy; } ;
struct ccw1 {int dummy; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int) ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int QETH_BUFSIZE ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qeth_cmd_buffer*) ; 
 void* kzalloc (unsigned int,int) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct qeth_cmd_buffer *qeth_alloc_cmd(struct qeth_channel *channel,
				       unsigned int length, unsigned int ccws,
				       long timeout)
{
	struct qeth_cmd_buffer *iob;

	if (length > QETH_BUFSIZE)
		return NULL;

	iob = kzalloc(sizeof(*iob), GFP_KERNEL);
	if (!iob)
		return NULL;

	iob->data = kzalloc(ALIGN(length, 8) + ccws * sizeof(struct ccw1),
			    GFP_KERNEL | GFP_DMA);
	if (!iob->data) {
		kfree(iob);
		return NULL;
	}

	init_completion(&iob->done);
	spin_lock_init(&iob->lock);
	INIT_LIST_HEAD(&iob->list);
	refcount_set(&iob->ref_count, 1);
	iob->channel = channel;
	iob->timeout = timeout;
	iob->length = length;
	return iob;
}