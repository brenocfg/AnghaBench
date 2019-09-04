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
struct TYPE_2__ {int ctrl; } ;
struct fritz_bcs {TYPE_1__ ctrl; scalar_t__ channel; struct fritz_adapter* adapter; } ;
struct fritz_adapter {scalar_t__ io; } ;

/* Variables and functions */
 scalar_t__ AVM_DATA ; 
 int AVM_IDX_HDLC_1 ; 
 int AVM_IDX_HDLC_2 ; 
 scalar_t__ AVM_INDEX ; 
 int /*<<< orphan*/  DBG (int,char*,scalar_t__,int,int) ; 
 scalar_t__ HDLC_CTRL ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static void __fcpci_write_ctrl(struct fritz_bcs *bcs, int which)
{
	struct fritz_adapter *adapter = bcs->adapter;
	int idx = bcs->channel ? AVM_IDX_HDLC_2 : AVM_IDX_HDLC_1;

	DBG(0x40, "hdlc %c wr%x ctrl %x",
	    'A' + bcs->channel, which, bcs->ctrl.ctrl);

	outl(idx, adapter->io + AVM_INDEX);
	outl(bcs->ctrl.ctrl, adapter->io + AVM_DATA + HDLC_CTRL);
}