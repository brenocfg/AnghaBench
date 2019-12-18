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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int QLC_BC_PAYLOAD_SZ ; 

__attribute__((used)) static u32 qlcnic_sriov_get_bc_paysize(u32 real_pay_size, u8 curr_frag)
{
	u32 pay_size;

	pay_size = real_pay_size / ((curr_frag + 1) * QLC_BC_PAYLOAD_SZ);

	if (pay_size)
		pay_size = QLC_BC_PAYLOAD_SZ;
	else
		pay_size = real_pay_size % QLC_BC_PAYLOAD_SZ;

	return pay_size;
}