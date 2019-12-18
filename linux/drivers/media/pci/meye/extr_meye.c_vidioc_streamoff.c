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
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__* grab_buffer; int /*<<< orphan*/  doneq; int /*<<< orphan*/  grabq; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEYE_BUF_UNUSED ; 
 int MEYE_MAX_BUFNBRS ; 
 int /*<<< orphan*/  kfifo_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mchip_hic_stop () ; 
 TYPE_2__ meye ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_streamoff(struct file *file, void *fh, enum v4l2_buf_type i)
{
	mutex_lock(&meye.lock);
	mchip_hic_stop();
	kfifo_reset(&meye.grabq);
	kfifo_reset(&meye.doneq);

	for (i = 0; i < MEYE_MAX_BUFNBRS; i++)
		meye.grab_buffer[i].state = MEYE_BUF_UNUSED;

	mutex_unlock(&meye.lock);
	return 0;
}