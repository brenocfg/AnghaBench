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
struct device {int dummy; } ;
struct cec_notifier {int /*<<< orphan*/  lock; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  conn_info; struct cec_adapter* cec_adap; } ;
struct cec_adapter {struct cec_notifier* notifier; int /*<<< orphan*/  conn_info; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct cec_notifier* cec_notifier_get_conn (struct device*,char const*) ; 
 int /*<<< orphan*/  cec_s_phys_addr (struct cec_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct cec_notifier *
cec_notifier_cec_adap_register(struct device *hdmi_dev, const char *conn_name,
			       struct cec_adapter *adap)
{
	struct cec_notifier *n;

	if (WARN_ON(!adap))
		return NULL;

	n = cec_notifier_get_conn(hdmi_dev, conn_name);
	if (!n)
		return n;

	mutex_lock(&n->lock);
	n->cec_adap = adap;
	adap->conn_info = n->conn_info;
	adap->notifier = n;
	cec_s_phys_addr(adap, n->phys_addr, false);
	mutex_unlock(&n->lock);
	return n;
}