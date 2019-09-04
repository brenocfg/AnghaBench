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
typedef  size_t u32 ;
struct vf_data_storage {int flags; scalar_t__ last_nack; } ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {struct vf_data_storage* vf_data; struct e1000_hw hw; } ;

/* Variables and functions */
 size_t E1000_VT_MSGTYPE_NACK ; 
 int HZ ; 
 int IGB_VF_FLAG_CTS ; 
 int /*<<< orphan*/  igb_write_mbx (struct e1000_hw*,size_t*,int,size_t) ; 
 scalar_t__ jiffies ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void igb_rcv_ack_from_vf(struct igb_adapter *adapter, u32 vf)
{
	struct e1000_hw *hw = &adapter->hw;
	struct vf_data_storage *vf_data = &adapter->vf_data[vf];
	u32 msg = E1000_VT_MSGTYPE_NACK;

	/* if device isn't clear to send it shouldn't be reading either */
	if (!(vf_data->flags & IGB_VF_FLAG_CTS) &&
	    time_after(jiffies, vf_data->last_nack + (2 * HZ))) {
		igb_write_mbx(hw, &msg, 1, vf);
		vf_data->last_nack = jiffies;
	}
}