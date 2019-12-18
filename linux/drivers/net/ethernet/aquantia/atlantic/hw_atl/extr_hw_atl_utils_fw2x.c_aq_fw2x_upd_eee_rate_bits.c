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
 int HW_ATL_FW2X_CAP_EEE_10G_MASK ; 
 int HW_ATL_FW2X_CAP_EEE_1G_MASK ; 
 int HW_ATL_FW2X_CAP_EEE_2G5_MASK ; 
 int HW_ATL_FW2X_CAP_EEE_5G_MASK ; 
 int eee_mask_to_fw2x (int) ; 

__attribute__((used)) static void aq_fw2x_upd_eee_rate_bits(struct aq_hw_s *self, u32 *mpi_opts,
				      u32 eee_speeds)
{
	*mpi_opts &= ~(HW_ATL_FW2X_CAP_EEE_1G_MASK |
		       HW_ATL_FW2X_CAP_EEE_2G5_MASK |
		       HW_ATL_FW2X_CAP_EEE_5G_MASK |
		       HW_ATL_FW2X_CAP_EEE_10G_MASK);

	*mpi_opts |= eee_mask_to_fw2x(eee_speeds);
}