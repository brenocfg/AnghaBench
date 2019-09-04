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
struct TYPE_2__ {int /*<<< orphan*/  ctrl; } ;
struct fritz_bcs {TYPE_1__ ctrl; scalar_t__ channel; struct fritz_adapter* adapter; } ;
struct fritz_adapter {scalar_t__ io; } ;

/* Variables and functions */
 int AVM_HDLC_STATUS_1 ; 
 int AVM_HDLC_STATUS_2 ; 
 int /*<<< orphan*/  DBG (int,char*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void fcpci2_write_ctrl(struct fritz_bcs *bcs, int which)
{
	struct fritz_adapter *adapter = bcs->adapter;
	int offset = bcs->channel ? AVM_HDLC_STATUS_2 : AVM_HDLC_STATUS_1;

	DBG(0x40, "hdlc %c wr%x ctrl %x",
	    'A' + bcs->channel, which, bcs->ctrl.ctrl);

	outl(bcs->ctrl.ctrl, adapter->io + offset);
}