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
struct smscore_device_t {int /*<<< orphan*/  bufferslock; int /*<<< orphan*/  buffers; int /*<<< orphan*/  buffer_mng_waitq; } ;
struct smscore_buffer_t {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void smscore_putbuffer(struct smscore_device_t *coredev,
		struct smscore_buffer_t *cb) {
	wake_up_interruptible(&coredev->buffer_mng_waitq);
	list_add_locked(&cb->entry, &coredev->buffers, &coredev->bufferslock);
}