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
struct cec_log_addrs {int dummy; } ;
struct cec_adapter {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __cec_s_log_addrs (struct cec_adapter*,struct cec_log_addrs*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int cec_s_log_addrs(struct cec_adapter *adap,
		    struct cec_log_addrs *log_addrs, bool block)
{
	int err;

	mutex_lock(&adap->lock);
	err = __cec_s_log_addrs(adap, log_addrs, block);
	mutex_unlock(&adap->lock);
	return err;
}