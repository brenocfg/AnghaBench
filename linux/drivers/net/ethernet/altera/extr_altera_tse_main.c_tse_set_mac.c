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
struct altera_tse_private {int /*<<< orphan*/  mac_dev; } ;

/* Variables and functions */
 int MAC_CMDCFG_RX_ENA ; 
 int MAC_CMDCFG_TX_ENA ; 
 int /*<<< orphan*/  command_config ; 
 int csrrd32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csrwr32 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tse_csroffs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tse_set_mac(struct altera_tse_private *priv, bool enable)
{
	u32 value = csrrd32(priv->mac_dev, tse_csroffs(command_config));

	if (enable)
		value |= MAC_CMDCFG_TX_ENA | MAC_CMDCFG_RX_ENA;
	else
		value &= ~(MAC_CMDCFG_TX_ENA | MAC_CMDCFG_RX_ENA);

	csrwr32(value, priv->mac_dev, tse_csroffs(command_config));
}