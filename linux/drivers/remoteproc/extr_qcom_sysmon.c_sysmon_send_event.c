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
struct qcom_sysmon {int ssr_ack; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  comp; int /*<<< orphan*/  ept; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int rpmsg_send (int /*<<< orphan*/ ,char*,int) ; 
 int snprintf (char*,int,char*,char const*) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sysmon_send_event(struct qcom_sysmon *sysmon, const char *name)
{
	char req[50];
	int len;
	int ret;

	len = snprintf(req, sizeof(req), "ssr:%s:before_shutdown", name);
	if (len >= sizeof(req))
		return;

	mutex_lock(&sysmon->lock);
	reinit_completion(&sysmon->comp);
	sysmon->ssr_ack = false;

	ret = rpmsg_send(sysmon->ept, req, len);
	if (ret < 0) {
		dev_err(sysmon->dev, "failed to send sysmon event\n");
		goto out_unlock;
	}

	ret = wait_for_completion_timeout(&sysmon->comp,
					  msecs_to_jiffies(5000));
	if (!ret) {
		dev_err(sysmon->dev, "timeout waiting for sysmon ack\n");
		goto out_unlock;
	}

	if (!sysmon->ssr_ack)
		dev_err(sysmon->dev, "unexpected response to sysmon event\n");

out_unlock:
	mutex_unlock(&sysmon->lock);
}