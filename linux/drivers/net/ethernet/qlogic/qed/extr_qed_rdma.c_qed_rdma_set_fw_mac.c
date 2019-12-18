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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 

void qed_rdma_set_fw_mac(u16 *p_fw_mac, u8 *p_qed_mac)
{
	p_fw_mac[0] = cpu_to_le16((p_qed_mac[0] << 8) + p_qed_mac[1]);
	p_fw_mac[1] = cpu_to_le16((p_qed_mac[2] << 8) + p_qed_mac[3]);
	p_fw_mac[2] = cpu_to_le16((p_qed_mac[4] << 8) + p_qed_mac[5]);
}