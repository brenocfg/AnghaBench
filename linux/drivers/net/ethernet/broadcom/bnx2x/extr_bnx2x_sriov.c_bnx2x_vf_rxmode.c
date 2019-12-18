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
struct bnx2x_virtf {int /*<<< orphan*/  abs_vfid; } ;
struct bnx2x_rx_mode_ramrod_params {int /*<<< orphan*/  rx_accept_flags; int /*<<< orphan*/  ramrod_flags; } ;
struct bnx2x {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  accept_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int bnx2x_config_rx_mode (struct bnx2x*,struct bnx2x_rx_mode_ramrod_params*) ; 
 int /*<<< orphan*/  bnx2x_vf_prep_rx_mode (struct bnx2x*,int,struct bnx2x_rx_mode_ramrod_params*,struct bnx2x_virtf*,unsigned long) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* vfq_get (struct bnx2x_virtf*,int) ; 

int bnx2x_vf_rxmode(struct bnx2x *bp, struct bnx2x_virtf *vf,
		    int qid, unsigned long accept_flags)
{
	struct bnx2x_rx_mode_ramrod_params ramrod;

	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->abs_vfid);

	bnx2x_vf_prep_rx_mode(bp, qid, &ramrod, vf, accept_flags);
	set_bit(RAMROD_COMP_WAIT, &ramrod.ramrod_flags);
	vfq_get(vf, qid)->accept_flags = ramrod.rx_accept_flags;
	return bnx2x_config_rx_mode(bp, &ramrod);
}