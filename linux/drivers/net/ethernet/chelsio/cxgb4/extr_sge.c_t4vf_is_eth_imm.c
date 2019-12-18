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
struct sk_buff {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int t4vf_is_eth_imm(const struct sk_buff *skb)
{
	/* The VF Driver uses the FW_ETH_TX_PKT_VM_WR firmware Work Request
	 * which does not accommodate immediate data.  We could dike out all
	 * of the support code for immediate data but that would tie our hands
	 * too much if we ever want to enhace the firmware.  It would also
	 * create more differences between the PF and VF Drivers.
	 */
	return false;
}