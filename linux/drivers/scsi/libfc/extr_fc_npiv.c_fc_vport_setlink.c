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
struct fc_vport {int dummy; } ;
struct fc_lport {int /*<<< orphan*/  lp_mutex; struct fc_vport* vport; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPORT_MUTEX_VN_PORT ; 
 int /*<<< orphan*/  __fc_vport_setlink (struct fc_lport*,struct fc_lport*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct fc_lport* shost_priv (struct Scsi_Host*) ; 
 struct Scsi_Host* vport_to_shost (struct fc_vport*) ; 

void fc_vport_setlink(struct fc_lport *vn_port)
{
	struct fc_vport *vport = vn_port->vport;
	struct Scsi_Host *shost = vport_to_shost(vport);
	struct fc_lport *n_port = shost_priv(shost);

	mutex_lock(&n_port->lp_mutex);
	mutex_lock_nested(&vn_port->lp_mutex, LPORT_MUTEX_VN_PORT);
	__fc_vport_setlink(n_port, vn_port);
	mutex_unlock(&vn_port->lp_mutex);
	mutex_unlock(&n_port->lp_mutex);
}