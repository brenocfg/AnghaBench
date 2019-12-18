#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/  disc_mutex; } ;
struct fc_lport {TYPE_3__* ptp_rdata; TYPE_2__ disc; int /*<<< orphan*/  lp_mutex; } ;
struct TYPE_6__ {void* node_name; void* port_name; } ;
struct TYPE_8__ {TYPE_1__ ids; int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  fc_lport_enter_ready (struct fc_lport*) ; 
 TYPE_3__* fc_rport_create (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_rport_destroy ; 
 int /*<<< orphan*/  fc_rport_login (TYPE_3__*) ; 
 int /*<<< orphan*/  fc_rport_logoff (TYPE_3__*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fc_lport_ptp_setup(struct fc_lport *lport,
			       u32 remote_fid, u64 remote_wwpn,
			       u64 remote_wwnn)
{
	lockdep_assert_held(&lport->lp_mutex);

	if (lport->ptp_rdata) {
		fc_rport_logoff(lport->ptp_rdata);
		kref_put(&lport->ptp_rdata->kref, fc_rport_destroy);
	}
	mutex_lock(&lport->disc.disc_mutex);
	lport->ptp_rdata = fc_rport_create(lport, remote_fid);
	kref_get(&lport->ptp_rdata->kref);
	lport->ptp_rdata->ids.port_name = remote_wwpn;
	lport->ptp_rdata->ids.node_name = remote_wwnn;
	mutex_unlock(&lport->disc.disc_mutex);

	fc_rport_login(lport->ptp_rdata);

	fc_lport_enter_ready(lport);
}