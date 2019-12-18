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
struct zfcp_fc_wka_port {scalar_t__ status; int /*<<< orphan*/  refcount; int /*<<< orphan*/  completion_wq; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EIO ; 
 int ERESTARTSYS ; 
 scalar_t__ ZFCP_FC_WKA_PORT_CLOSING ; 
 scalar_t__ ZFCP_FC_WKA_PORT_OFFLINE ; 
 scalar_t__ ZFCP_FC_WKA_PORT_ONLINE ; 
 scalar_t__ ZFCP_FC_WKA_PORT_OPENING ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 scalar_t__ zfcp_fsf_open_wka_port (struct zfcp_fc_wka_port*) ; 

__attribute__((used)) static int zfcp_fc_wka_port_get(struct zfcp_fc_wka_port *wka_port)
{
	if (mutex_lock_interruptible(&wka_port->mutex))
		return -ERESTARTSYS;

	if (wka_port->status == ZFCP_FC_WKA_PORT_OFFLINE ||
	    wka_port->status == ZFCP_FC_WKA_PORT_CLOSING) {
		wka_port->status = ZFCP_FC_WKA_PORT_OPENING;
		if (zfcp_fsf_open_wka_port(wka_port))
			wka_port->status = ZFCP_FC_WKA_PORT_OFFLINE;
	}

	mutex_unlock(&wka_port->mutex);

	wait_event(wka_port->completion_wq,
		   wka_port->status == ZFCP_FC_WKA_PORT_ONLINE ||
		   wka_port->status == ZFCP_FC_WKA_PORT_OFFLINE);

	if (wka_port->status == ZFCP_FC_WKA_PORT_ONLINE) {
		atomic_inc(&wka_port->refcount);
		return 0;
	}
	return -EIO;
}