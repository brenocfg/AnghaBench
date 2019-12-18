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
typedef  int u32 ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int AQ_NIC_FC_RX ; 
 int AQ_NIC_FC_TX ; 
 int HW_ATL_FW2X_CAP_ASYM_PAUSE ; 
 int HW_ATL_FW2X_CAP_PAUSE ; 
 int aq_fw2x_state2_get (struct aq_hw_s*) ; 

__attribute__((used)) static u32 aq_fw2x_get_flow_control(struct aq_hw_s *self, u32 *fcmode)
{
	u32 mpi_state = aq_fw2x_state2_get(self);

	if (mpi_state & HW_ATL_FW2X_CAP_PAUSE)
		if (mpi_state & HW_ATL_FW2X_CAP_ASYM_PAUSE)
			*fcmode = AQ_NIC_FC_RX;
		else
			*fcmode = AQ_NIC_FC_RX | AQ_NIC_FC_TX;
	else
		if (mpi_state & HW_ATL_FW2X_CAP_ASYM_PAUSE)
			*fcmode = AQ_NIC_FC_TX;
		else
			*fcmode = 0;

	return 0;
}