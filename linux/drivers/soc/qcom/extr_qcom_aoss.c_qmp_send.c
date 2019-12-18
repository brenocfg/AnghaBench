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
typedef  int /*<<< orphan*/  u32 ;
struct qmp {size_t size; int /*<<< orphan*/  tx_lock; scalar_t__ offset; scalar_t__ msgram; int /*<<< orphan*/  dev; int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 scalar_t__ WARN_ON (size_t) ; 
 int /*<<< orphan*/  __iowrite32_copy (scalar_t__,void const*,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qmp_kick (struct qmp*) ; 
 int /*<<< orphan*/  qmp_message_empty (struct qmp*) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (size_t,scalar_t__) ; 

__attribute__((used)) static int qmp_send(struct qmp *qmp, const void *data, size_t len)
{
	long time_left;
	int ret;

	if (WARN_ON(len + sizeof(u32) > qmp->size))
		return -EINVAL;

	if (WARN_ON(len % sizeof(u32)))
		return -EINVAL;

	mutex_lock(&qmp->tx_lock);

	/* The message RAM only implements 32-bit accesses */
	__iowrite32_copy(qmp->msgram + qmp->offset + sizeof(u32),
			 data, len / sizeof(u32));
	writel(len, qmp->msgram + qmp->offset);
	qmp_kick(qmp);

	time_left = wait_event_interruptible_timeout(qmp->event,
						     qmp_message_empty(qmp), HZ);
	if (!time_left) {
		dev_err(qmp->dev, "ucore did not ack channel\n");
		ret = -ETIMEDOUT;

		/* Clear message from buffer */
		writel(0, qmp->msgram + qmp->offset);
	} else {
		ret = 0;
	}

	mutex_unlock(&qmp->tx_lock);

	return ret;
}