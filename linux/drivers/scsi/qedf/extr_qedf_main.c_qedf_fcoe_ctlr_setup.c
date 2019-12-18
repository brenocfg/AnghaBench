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
struct TYPE_2__ {int /*<<< orphan*/  ctl_src_addr; int /*<<< orphan*/  get_src_addr; int /*<<< orphan*/  send; } ;
struct qedf_ctx {int /*<<< orphan*/  mac; TYPE_1__ ctlr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIP_MODE_AUTO ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcoe_ctlr_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedf_fip_send ; 
 int /*<<< orphan*/  qedf_get_src_mac ; 

__attribute__((used)) static void qedf_fcoe_ctlr_setup(struct qedf_ctx *qedf)
{
	fcoe_ctlr_init(&qedf->ctlr, FIP_MODE_AUTO);

	qedf->ctlr.send = qedf_fip_send;
	qedf->ctlr.get_src_addr = qedf_get_src_mac;
	ether_addr_copy(qedf->ctlr.ctl_src_addr, qedf->mac);
}