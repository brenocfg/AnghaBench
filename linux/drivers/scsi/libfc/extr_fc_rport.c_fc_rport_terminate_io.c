#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fc_rport_libfc_priv {struct fc_lport* local_port; } ;
struct fc_rport {int /*<<< orphan*/  port_id; struct fc_rport_libfc_priv* dd_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* exch_mgr_reset ) (struct fc_lport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct fc_lport {TYPE_1__ tt; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct fc_lport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct fc_lport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fc_rport_terminate_io(struct fc_rport *rport)
{
	struct fc_rport_libfc_priv *rpriv = rport->dd_data;
	struct fc_lport *lport = rpriv->local_port;

	lport->tt.exch_mgr_reset(lport, 0, rport->port_id);
	lport->tt.exch_mgr_reset(lport, rport->port_id, 0);
}