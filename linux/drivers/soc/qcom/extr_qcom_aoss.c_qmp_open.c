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
typedef  scalar_t__ u32 ;
struct qmp {scalar_t__ msgram; int /*<<< orphan*/  dev; int /*<<< orphan*/  event; scalar_t__ size; scalar_t__ offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 scalar_t__ QMP_DESC_MCORE_CH_STATE ; 
 scalar_t__ QMP_DESC_MCORE_LINK_STATE ; 
 scalar_t__ QMP_DESC_MCORE_MBOX_OFFSET ; 
 scalar_t__ QMP_DESC_MCORE_MBOX_SIZE ; 
 scalar_t__ QMP_DESC_UCORE_CH_STATE_ACK ; 
 scalar_t__ QMP_DESC_UCORE_LINK_STATE ; 
 scalar_t__ QMP_DESC_UCORE_LINK_STATE_ACK ; 
 scalar_t__ QMP_DESC_VERSION ; 
 scalar_t__ QMP_STATE_DOWN ; 
 scalar_t__ QMP_STATE_UP ; 
 scalar_t__ QMP_VERSION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  qmp_kick (struct qmp*) ; 
 int /*<<< orphan*/  qmp_link_acked (struct qmp*) ; 
 int /*<<< orphan*/  qmp_magic_valid (struct qmp*) ; 
 int /*<<< orphan*/  qmp_mcore_channel_acked (struct qmp*) ; 
 int /*<<< orphan*/  qmp_ucore_channel_up (struct qmp*) ; 
 scalar_t__ readl (scalar_t__) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int qmp_open(struct qmp *qmp)
{
	int ret;
	u32 val;

	if (!qmp_magic_valid(qmp)) {
		dev_err(qmp->dev, "QMP magic doesn't match\n");
		return -EINVAL;
	}

	val = readl(qmp->msgram + QMP_DESC_VERSION);
	if (val != QMP_VERSION) {
		dev_err(qmp->dev, "unsupported QMP version %d\n", val);
		return -EINVAL;
	}

	qmp->offset = readl(qmp->msgram + QMP_DESC_MCORE_MBOX_OFFSET);
	qmp->size = readl(qmp->msgram + QMP_DESC_MCORE_MBOX_SIZE);
	if (!qmp->size) {
		dev_err(qmp->dev, "invalid mailbox size\n");
		return -EINVAL;
	}

	/* Ack remote core's link state */
	val = readl(qmp->msgram + QMP_DESC_UCORE_LINK_STATE);
	writel(val, qmp->msgram + QMP_DESC_UCORE_LINK_STATE_ACK);

	/* Set local core's link state to up */
	writel(QMP_STATE_UP, qmp->msgram + QMP_DESC_MCORE_LINK_STATE);

	qmp_kick(qmp);

	ret = wait_event_timeout(qmp->event, qmp_link_acked(qmp), HZ);
	if (!ret) {
		dev_err(qmp->dev, "ucore didn't ack link\n");
		goto timeout_close_link;
	}

	writel(QMP_STATE_UP, qmp->msgram + QMP_DESC_MCORE_CH_STATE);

	qmp_kick(qmp);

	ret = wait_event_timeout(qmp->event, qmp_ucore_channel_up(qmp), HZ);
	if (!ret) {
		dev_err(qmp->dev, "ucore didn't open channel\n");
		goto timeout_close_channel;
	}

	/* Ack remote core's channel state */
	writel(QMP_STATE_UP, qmp->msgram + QMP_DESC_UCORE_CH_STATE_ACK);

	qmp_kick(qmp);

	ret = wait_event_timeout(qmp->event, qmp_mcore_channel_acked(qmp), HZ);
	if (!ret) {
		dev_err(qmp->dev, "ucore didn't ack channel\n");
		goto timeout_close_channel;
	}

	return 0;

timeout_close_channel:
	writel(QMP_STATE_DOWN, qmp->msgram + QMP_DESC_MCORE_CH_STATE);

timeout_close_link:
	writel(QMP_STATE_DOWN, qmp->msgram + QMP_DESC_MCORE_LINK_STATE);
	qmp_kick(qmp);

	return -ETIMEDOUT;
}