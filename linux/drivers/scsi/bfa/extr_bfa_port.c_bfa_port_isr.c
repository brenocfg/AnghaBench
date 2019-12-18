#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  status; } ;
struct TYPE_9__ {int /*<<< orphan*/  status; } ;
struct TYPE_8__ {int /*<<< orphan*/  status; } ;
struct TYPE_7__ {int /*<<< orphan*/  status; } ;
union bfi_port_i2h_msg_u {TYPE_5__ clearstats_rsp; TYPE_4__ getstats_rsp; TYPE_3__ disable_rsp; TYPE_2__ enable_rsp; } ;
struct TYPE_6__ {int /*<<< orphan*/  msg_id; } ;
struct bfi_mbmsg_s {TYPE_1__ mh; } ;
struct bfa_port_s {int /*<<< orphan*/  stats_busy; int /*<<< orphan*/  endis_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
#define  BFI_PORT_I2H_CLEAR_STATS_RSP 131 
#define  BFI_PORT_I2H_DISABLE_RSP 130 
#define  BFI_PORT_I2H_ENABLE_RSP 129 
#define  BFI_PORT_I2H_GET_STATS_RSP 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_port_clear_stats_isr (struct bfa_port_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_port_disable_isr (struct bfa_port_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_port_enable_isr (struct bfa_port_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_port_get_stats_isr (struct bfa_port_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_port_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_port_isr(void *cbarg, struct bfi_mbmsg_s *m)
{
	struct bfa_port_s *port = (struct bfa_port_s *) cbarg;
	union bfi_port_i2h_msg_u *i2hmsg;

	i2hmsg = (union bfi_port_i2h_msg_u *) m;
	bfa_trc(port, m->mh.msg_id);

	switch (m->mh.msg_id) {
	case BFI_PORT_I2H_ENABLE_RSP:
		if (port->endis_pending == BFA_FALSE)
			break;
		bfa_port_enable_isr(port, i2hmsg->enable_rsp.status);
		break;

	case BFI_PORT_I2H_DISABLE_RSP:
		if (port->endis_pending == BFA_FALSE)
			break;
		bfa_port_disable_isr(port, i2hmsg->disable_rsp.status);
		break;

	case BFI_PORT_I2H_GET_STATS_RSP:
		/* Stats busy flag is still set? (may be cmd timed out) */
		if (port->stats_busy == BFA_FALSE)
			break;
		bfa_port_get_stats_isr(port, i2hmsg->getstats_rsp.status);
		break;

	case BFI_PORT_I2H_CLEAR_STATS_RSP:
		if (port->stats_busy == BFA_FALSE)
			break;
		bfa_port_clear_stats_isr(port, i2hmsg->clearstats_rsp.status);
		break;

	default:
		WARN_ON(1);
	}
}