#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {int f_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__* grab_buffer; int /*<<< orphan*/  doneq_lock; int /*<<< orphan*/  doneq; int /*<<< orphan*/  proc_list; } ;
struct TYPE_3__ {int state; int size; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int EINVAL ; 
#define  MEYE_BUF_DONE 130 
#define  MEYE_BUF_UNUSED 129 
#define  MEYE_BUF_USING 128 
 int O_NONBLOCK ; 
 int gbuffers ; 
 int kfifo_out_locked (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ *) ; 
 TYPE_2__ meye ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int meyeioc_sync(struct file *file, void *fh, int *i)
{
	int unused;

	if (*i < 0 || *i >= gbuffers)
		return -EINVAL;

	mutex_lock(&meye.lock);
	switch (meye.grab_buffer[*i].state) {

	case MEYE_BUF_UNUSED:
		mutex_unlock(&meye.lock);
		return -EINVAL;
	case MEYE_BUF_USING:
		if (file->f_flags & O_NONBLOCK) {
			mutex_unlock(&meye.lock);
			return -EAGAIN;
		}
		if (wait_event_interruptible(meye.proc_list,
			(meye.grab_buffer[*i].state != MEYE_BUF_USING))) {
			mutex_unlock(&meye.lock);
			return -EINTR;
		}
		/* fall through */
	case MEYE_BUF_DONE:
		meye.grab_buffer[*i].state = MEYE_BUF_UNUSED;
		if (kfifo_out_locked(&meye.doneq, (unsigned char *)&unused,
				sizeof(int), &meye.doneq_lock) != sizeof(int))
					break;
	}
	*i = meye.grab_buffer[*i].size;
	mutex_unlock(&meye.lock);
	return 0;
}