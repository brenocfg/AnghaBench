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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 scalar_t__ NIC_PF_VF_0_127_MAILBOX_0_1 ; 
 int NIC_VF_NUM_SHIFT ; 

__attribute__((used)) static u64 nic_get_mbx_addr(int vf)
{
	return NIC_PF_VF_0_127_MAILBOX_0_1 + (vf << NIC_VF_NUM_SHIFT);
}