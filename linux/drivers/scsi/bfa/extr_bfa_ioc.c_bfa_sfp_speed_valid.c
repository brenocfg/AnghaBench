#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ mb100; scalar_t__ mb200; scalar_t__ mb400; scalar_t__ mb800; scalar_t__ mb1600; } ;
union sfp_xcvr_fc3_code_u {int b; TYPE_3__ r; } ;
struct TYPE_5__ {scalar_t__ e10g_lr; scalar_t__ e10g_sr; } ;
union sfp_xcvr_e10g_code_u {int b; TYPE_2__ r; } ;
struct sfp_xcvr_s {union sfp_xcvr_e10g_code_u e10g; union sfp_xcvr_fc3_code_u fc3; } ;
struct TYPE_4__ {scalar_t__ xcvr; } ;
struct sfp_mem_s {TYPE_1__ srlid_base; } ;
struct bfa_sfp_s {scalar_t__ dbuf_kva; } ;
typedef  enum bfa_port_speed { ____Placeholder_bfa_port_speed } bfa_port_speed ;
typedef  int /*<<< orphan*/  bfa_status_t ;

/* Variables and functions */
 int BFA_PORT_SPEED_10GBPS ; 
 int BFA_PORT_SPEED_16GBPS ; 
 int BFA_PORT_SPEED_1GBPS ; 
 int BFA_PORT_SPEED_2GBPS ; 
 int BFA_PORT_SPEED_4GBPS ; 
 int BFA_PORT_SPEED_8GBPS ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  BFA_STATUS_UNSUPP_SPEED ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_sfp_s*,int) ; 

__attribute__((used)) static bfa_status_t
bfa_sfp_speed_valid(struct bfa_sfp_s *sfp, enum bfa_port_speed portspeed)
{
	struct sfp_mem_s *sfpmem = (struct sfp_mem_s *)sfp->dbuf_kva;
	struct sfp_xcvr_s *xcvr = (struct sfp_xcvr_s *) sfpmem->srlid_base.xcvr;
	union sfp_xcvr_fc3_code_u fc3 = xcvr->fc3;
	union sfp_xcvr_e10g_code_u e10g = xcvr->e10g;

	if (portspeed == BFA_PORT_SPEED_10GBPS) {
		if (e10g.r.e10g_sr || e10g.r.e10g_lr)
			return BFA_STATUS_OK;
		else {
			bfa_trc(sfp, e10g.b);
			return BFA_STATUS_UNSUPP_SPEED;
		}
	}
	if (((portspeed & BFA_PORT_SPEED_16GBPS) && fc3.r.mb1600) ||
	    ((portspeed & BFA_PORT_SPEED_8GBPS) && fc3.r.mb800) ||
	    ((portspeed & BFA_PORT_SPEED_4GBPS) && fc3.r.mb400) ||
	    ((portspeed & BFA_PORT_SPEED_2GBPS) && fc3.r.mb200) ||
	    ((portspeed & BFA_PORT_SPEED_1GBPS) && fc3.r.mb100))
		return BFA_STATUS_OK;
	else {
		bfa_trc(sfp, portspeed);
		bfa_trc(sfp, fc3.b);
		bfa_trc(sfp, e10g.b);
		return BFA_STATUS_UNSUPP_SPEED;
	}
}