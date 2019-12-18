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
struct cec_connector_info {int dummy; } ;
struct cec_notifier {int /*<<< orphan*/  lock; scalar_t__ cec_adap; struct cec_connector_info conn_info; int /*<<< orphan*/  phys_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_PHYS_ADDR_INVALID ; 
 struct cec_notifier* cec_notifier_get_conn (struct device*,char const*) ; 
 int /*<<< orphan*/  cec_phys_addr_invalidate (scalar_t__) ; 
 int /*<<< orphan*/  cec_s_conn_info (scalar_t__,struct cec_connector_info const*) ; 
 int /*<<< orphan*/  memset (struct cec_connector_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct cec_notifier *
cec_notifier_conn_register(struct device *hdmi_dev, const char *conn_name,
			   const struct cec_connector_info *conn_info)
{
	struct cec_notifier *n = cec_notifier_get_conn(hdmi_dev, conn_name);

	if (!n)
		return n;

	mutex_lock(&n->lock);
	n->phys_addr = CEC_PHYS_ADDR_INVALID;
	if (conn_info)
		n->conn_info = *conn_info;
	else
		memset(&n->conn_info, 0, sizeof(n->conn_info));
	if (n->cec_adap) {
		cec_phys_addr_invalidate(n->cec_adap);
		cec_s_conn_info(n->cec_adap, conn_info);
	}
	mutex_unlock(&n->lock);
	return n;
}