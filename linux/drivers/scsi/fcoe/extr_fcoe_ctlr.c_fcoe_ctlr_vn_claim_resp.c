#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  port_id; } ;
struct TYPE_4__ {TYPE_1__ ids; } ;
struct fcoe_rport {TYPE_2__ rdata; } ;
struct fcoe_ctlr {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ FIP_ST_VNMP_CLAIM ; 
 scalar_t__ FIP_ST_VNMP_UP ; 
 int /*<<< orphan*/  LIBFCOE_FIP_DBG (struct fcoe_ctlr*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcoe_ctlr_state (scalar_t__) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_add (struct fcoe_ctlr*,struct fcoe_rport*) ; 

__attribute__((used)) static void fcoe_ctlr_vn_claim_resp(struct fcoe_ctlr *fip,
				    struct fcoe_rport *new)
{
	LIBFCOE_FIP_DBG(fip, "claim resp from from rport %x - state %s\n",
			new->rdata.ids.port_id, fcoe_ctlr_state(fip->state));
	if (fip->state == FIP_ST_VNMP_UP || fip->state == FIP_ST_VNMP_CLAIM)
		fcoe_ctlr_vn_add(fip, new);
}