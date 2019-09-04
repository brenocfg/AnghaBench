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
typedef  int u32 ;
struct TYPE_6__ {scalar_t__ hw_addr; } ;
struct TYPE_5__ {int count; } ;
struct TYPE_4__ {int count; } ;
struct atl1_adapter {TYPE_3__ hw; TYPE_2__ rrd_ring; TYPE_1__ rfd_ring; } ;

/* Variables and functions */
 scalar_t__ REG_RXQ_RRD_PAUSE_THRESH ; 
 scalar_t__ REG_RXQ_RXF_PAUSE_THRESH ; 
 int RXQ_RRD_PAUSE_TH_HI_MASK ; 
 int RXQ_RRD_PAUSE_TH_HI_SHIFT ; 
 int RXQ_RRD_PAUSE_TH_LO_MASK ; 
 int RXQ_RRD_PAUSE_TH_LO_SHIFT ; 
 int RXQ_RXF_PAUSE_TH_HI_MASK ; 
 int RXQ_RXF_PAUSE_TH_HI_SHIFT ; 
 int RXQ_RXF_PAUSE_TH_LO_MASK ; 
 int RXQ_RXF_PAUSE_TH_LO_SHIFT ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void set_flow_ctrl_old(struct atl1_adapter *adapter)
{
	u32 hi, lo, value;

	/* RFD Flow Control */
	value = adapter->rfd_ring.count;
	hi = value / 16;
	if (hi < 2)
		hi = 2;
	lo = value * 7 / 8;

	value = ((hi & RXQ_RXF_PAUSE_TH_HI_MASK) << RXQ_RXF_PAUSE_TH_HI_SHIFT) |
		((lo & RXQ_RXF_PAUSE_TH_LO_MASK) << RXQ_RXF_PAUSE_TH_LO_SHIFT);
	iowrite32(value, adapter->hw.hw_addr + REG_RXQ_RXF_PAUSE_THRESH);

	/* RRD Flow Control */
	value = adapter->rrd_ring.count;
	lo = value / 16;
	hi = value * 7 / 8;
	if (lo < 2)
		lo = 2;
	value = ((hi & RXQ_RRD_PAUSE_TH_HI_MASK) << RXQ_RRD_PAUSE_TH_HI_SHIFT) |
		((lo & RXQ_RRD_PAUSE_TH_LO_MASK) << RXQ_RRD_PAUSE_TH_LO_SHIFT);
	iowrite32(value, adapter->hw.hw_addr + REG_RXQ_RRD_PAUSE_THRESH);
}