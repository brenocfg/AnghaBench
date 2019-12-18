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
struct cec_connector_info {int dummy; } ;
struct cec_adapter {int capabilities; int /*<<< orphan*/  lock; struct cec_connector_info conn_info; } ;

/* Variables and functions */
 int CEC_CAP_CONNECTOR_INFO ; 
 scalar_t__ IS_ERR_OR_NULL (struct cec_adapter*) ; 
 int /*<<< orphan*/  cec_post_state_event (struct cec_adapter*) ; 
 int /*<<< orphan*/  memset (struct cec_connector_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void cec_s_conn_info(struct cec_adapter *adap,
		     const struct cec_connector_info *conn_info)
{
	if (IS_ERR_OR_NULL(adap))
		return;

	if (!(adap->capabilities & CEC_CAP_CONNECTOR_INFO))
		return;

	mutex_lock(&adap->lock);
	if (conn_info)
		adap->conn_info = *conn_info;
	else
		memset(&adap->conn_info, 0, sizeof(adap->conn_info));
	cec_post_state_event(adap);
	mutex_unlock(&adap->lock);
}