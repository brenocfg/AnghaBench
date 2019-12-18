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
struct rpmsg_endpoint {int dummy; } ;
struct qcom_smd_endpoint {struct qcom_smd_channel* qsch; } ;
struct qcom_smd_channel {int /*<<< orphan*/  fblockread_event; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLOUT ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int qcom_smd_get_tx_avail (struct qcom_smd_channel*) ; 
 struct qcom_smd_endpoint* to_smd_endpoint (struct rpmsg_endpoint*) ; 

__attribute__((used)) static __poll_t qcom_smd_poll(struct rpmsg_endpoint *ept,
				  struct file *filp, poll_table *wait)
{
	struct qcom_smd_endpoint *qsept = to_smd_endpoint(ept);
	struct qcom_smd_channel *channel = qsept->qsch;
	__poll_t mask = 0;

	poll_wait(filp, &channel->fblockread_event, wait);

	if (qcom_smd_get_tx_avail(channel) > 20)
		mask |= EPOLLOUT | EPOLLWRNORM;

	return mask;
}