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
struct cec_msg {int dummy; } ;
struct cec_adapter {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int cec_transmit_msg_fh (struct cec_adapter*,struct cec_msg*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int cec_transmit_msg(struct cec_adapter *adap, struct cec_msg *msg,
		     bool block)
{
	int ret;

	mutex_lock(&adap->lock);
	ret = cec_transmit_msg_fh(adap, msg, NULL, block);
	mutex_unlock(&adap->lock);
	return ret;
}