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
 int /*<<< orphan*/  LAN9303_MAC_RX_CFG_0 ; 
 int LAN9303_MAC_RX_CFG_X_REJECT_MAC_TYPES ; 
 int LAN9303_MAC_RX_CFG_X_RX_ENABLE ; 
 int /*<<< orphan*/  LAN9303_MAC_TX_CFG_0 ; 
 int LAN9303_MAC_TX_CFG_X_TX_ENABLE ; 
 int LAN9303_MAC_TX_CFG_X_TX_IFG_CONFIG_DEFAULT ; 
 int LAN9303_MAC_TX_CFG_X_TX_PAD_ENABLE ; 
 int lan9303_write_switch_port (struct lan9303*,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lan9303_enable_processing_port(struct lan9303 *chip,
					  unsigned int port)
{
	int ret;

	/* enable RX and keep register reset default values else */
	ret = lan9303_write_switch_port(chip, port, LAN9303_MAC_RX_CFG_0,
					LAN9303_MAC_RX_CFG_X_REJECT_MAC_TYPES |
					LAN9303_MAC_RX_CFG_X_RX_ENABLE);
	if (ret)
		return ret;

	/* enable TX and keep register reset default values else */
	return lan9303_write_switch_port(chip, port, LAN9303_MAC_TX_CFG_0,
				LAN9303_MAC_TX_CFG_X_TX_IFG_CONFIG_DEFAULT |
				LAN9303_MAC_TX_CFG_X_TX_PAD_ENABLE |
				LAN9303_MAC_TX_CFG_X_TX_ENABLE);
}