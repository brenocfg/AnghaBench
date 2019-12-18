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
struct fc_vport {struct fc_lport* dd_data; } ;
struct fc_lport {int /*<<< orphan*/  lp_mutex; int /*<<< orphan*/  list; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fcoe_config_mutex ; 
 int /*<<< orphan*/  fcoe_if_destroy (struct fc_lport*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 struct fc_lport* shost_priv (struct Scsi_Host*) ; 
 struct Scsi_Host* vport_to_shost (struct fc_vport*) ; 

__attribute__((used)) static int fcoe_vport_destroy(struct fc_vport *vport)
{
	struct Scsi_Host *shost = vport_to_shost(vport);
	struct fc_lport *n_port = shost_priv(shost);
	struct fc_lport *vn_port = vport->dd_data;

	mutex_lock(&n_port->lp_mutex);
	list_del(&vn_port->list);
	mutex_unlock(&n_port->lp_mutex);

	mutex_lock(&fcoe_config_mutex);
	rtnl_lock();
	fcoe_if_destroy(vn_port);
	rtnl_unlock();
	mutex_unlock(&fcoe_config_mutex);

	return 0;
}