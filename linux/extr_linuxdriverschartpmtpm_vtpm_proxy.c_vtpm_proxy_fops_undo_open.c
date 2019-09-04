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
struct proxy_dev {int /*<<< orphan*/  wq; int /*<<< orphan*/  buf_lock; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_OPENED_FLAG ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vtpm_proxy_fops_undo_open(struct proxy_dev *proxy_dev)
{
	mutex_lock(&proxy_dev->buf_lock);

	proxy_dev->state &= ~STATE_OPENED_FLAG;

	mutex_unlock(&proxy_dev->buf_lock);

	/* no more TPM responses -- wake up anyone waiting for them */
	wake_up_interruptible(&proxy_dev->wq);
}