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
typedef  int u8 ;
struct TYPE_2__ {int* hw_mac_addr; } ;
struct qed_hwfn {TYPE_1__ hw_info; } ;

/* Variables and functions */

__attribute__((used)) static void qed_rdma_get_guid(struct qed_hwfn *p_hwfn, u8 *guid)
{
	guid[0] = p_hwfn->hw_info.hw_mac_addr[0] ^ 2;
	guid[1] = p_hwfn->hw_info.hw_mac_addr[1];
	guid[2] = p_hwfn->hw_info.hw_mac_addr[2];
	guid[3] = 0xff;
	guid[4] = 0xfe;
	guid[5] = p_hwfn->hw_info.hw_mac_addr[3];
	guid[6] = p_hwfn->hw_info.hw_mac_addr[4];
	guid[7] = p_hwfn->hw_info.hw_mac_addr[5];
}