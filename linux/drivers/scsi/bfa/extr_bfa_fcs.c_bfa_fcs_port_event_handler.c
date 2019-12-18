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
struct bfa_fcs_s {int /*<<< orphan*/  fabric; } ;
typedef  enum bfa_port_linkstate { ____Placeholder_bfa_port_linkstate } bfa_port_linkstate ;

/* Variables and functions */
#define  BFA_PORT_LINKDOWN 129 
#define  BFA_PORT_LINKUP 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_link_down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_link_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_fcs_s*,int) ; 

__attribute__((used)) static void
bfa_fcs_port_event_handler(void *cbarg, enum bfa_port_linkstate event)
{
	struct bfa_fcs_s      *fcs = cbarg;

	bfa_trc(fcs, event);

	switch (event) {
	case BFA_PORT_LINKUP:
		bfa_fcs_fabric_link_up(&fcs->fabric);
		break;

	case BFA_PORT_LINKDOWN:
		bfa_fcs_fabric_link_down(&fcs->fabric);
		break;

	default:
		WARN_ON(1);
	}
}