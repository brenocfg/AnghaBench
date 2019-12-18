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
struct lan9303 {int /*<<< orphan*/  swe_port_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAN9303_SWE_PORT_MIRROR ; 
 int /*<<< orphan*/  LAN9303_SWE_PORT_MIRROR_DISABLED ; 
 int /*<<< orphan*/  LAN9303_SWE_PORT_STATE ; 
 int /*<<< orphan*/  eth_stp_addr ; 
 int /*<<< orphan*/  lan9303_alr_add_port (struct lan9303*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lan9303_write_switch_reg (struct lan9303*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lan9303_bridge_ports(struct lan9303 *chip)
{
	/* ports bridged: remove mirroring */
	lan9303_write_switch_reg(chip, LAN9303_SWE_PORT_MIRROR,
				 LAN9303_SWE_PORT_MIRROR_DISABLED);

	lan9303_write_switch_reg(chip, LAN9303_SWE_PORT_STATE,
				 chip->swe_port_state);
	lan9303_alr_add_port(chip, eth_stp_addr, 0, true);
}