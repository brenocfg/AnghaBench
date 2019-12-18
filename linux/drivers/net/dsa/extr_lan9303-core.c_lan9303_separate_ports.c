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
struct lan9303 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAN9303_SWE_PORT_MIRROR ; 
 int LAN9303_SWE_PORT_MIRROR_ENABLE_RX_MIRRORING ; 
 int LAN9303_SWE_PORT_MIRROR_MIRRORED_PORT1 ; 
 int LAN9303_SWE_PORT_MIRROR_MIRRORED_PORT2 ; 
 int LAN9303_SWE_PORT_MIRROR_SNIFFER_PORT0 ; 
 int LAN9303_SWE_PORT_MIRROR_SNIFF_ALL ; 
 int /*<<< orphan*/  LAN9303_SWE_PORT_STATE ; 
 int LAN9303_SWE_PORT_STATE_BLOCKING_PORT1 ; 
 int LAN9303_SWE_PORT_STATE_BLOCKING_PORT2 ; 
 int LAN9303_SWE_PORT_STATE_FORWARDING_PORT0 ; 
 int /*<<< orphan*/  eth_stp_addr ; 
 int /*<<< orphan*/  lan9303_alr_del_port (struct lan9303*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lan9303_write_switch_reg (struct lan9303*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lan9303_separate_ports(struct lan9303 *chip)
{
	int ret;

	lan9303_alr_del_port(chip, eth_stp_addr, 0);
	ret = lan9303_write_switch_reg(chip, LAN9303_SWE_PORT_MIRROR,
				LAN9303_SWE_PORT_MIRROR_SNIFFER_PORT0 |
				LAN9303_SWE_PORT_MIRROR_MIRRORED_PORT1 |
				LAN9303_SWE_PORT_MIRROR_MIRRORED_PORT2 |
				LAN9303_SWE_PORT_MIRROR_ENABLE_RX_MIRRORING |
				LAN9303_SWE_PORT_MIRROR_SNIFF_ALL);
	if (ret)
		return ret;

	/* prevent port 1 and 2 from forwarding packets by their own */
	return lan9303_write_switch_reg(chip, LAN9303_SWE_PORT_STATE,
				LAN9303_SWE_PORT_STATE_FORWARDING_PORT0 |
				LAN9303_SWE_PORT_STATE_BLOCKING_PORT1 |
				LAN9303_SWE_PORT_STATE_BLOCKING_PORT2);
}