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
struct cec_adapter {int is_configuring; int /*<<< orphan*/  lock; int /*<<< orphan*/  config_completion; int /*<<< orphan*/ * kthread_config; int /*<<< orphan*/  name; scalar_t__ is_configured; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cec_config_thread_func ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct cec_adapter*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cec_claim_log_addrs(struct cec_adapter *adap, bool block)
{
	if (WARN_ON(adap->is_configuring || adap->is_configured))
		return;

	init_completion(&adap->config_completion);

	/* Ready to kick off the thread */
	adap->is_configuring = true;
	adap->kthread_config = kthread_run(cec_config_thread_func, adap,
					   "ceccfg-%s", adap->name);
	if (IS_ERR(adap->kthread_config)) {
		adap->kthread_config = NULL;
	} else if (block) {
		mutex_unlock(&adap->lock);
		wait_for_completion(&adap->config_completion);
		mutex_lock(&adap->lock);
	}
}