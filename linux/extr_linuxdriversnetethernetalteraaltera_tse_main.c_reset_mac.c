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
 int ALTERA_TSE_SW_RESET_WATCHDOG_CNTR ; 
 int MAC_CMDCFG_CNT_RESET ; 
 int MAC_CMDCFG_RX_ENA ; 
 int MAC_CMDCFG_SW_RESET ; 
 int MAC_CMDCFG_TX_ENA ; 
 int /*<<< orphan*/  command_config ; 
 int csrrd32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csrwr32 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tse_bit_is_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tse_csroffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int reset_mac(struct altera_tse_private *priv)
{
	int counter;
	u32 dat;

	dat = csrrd32(priv->mac_dev, tse_csroffs(command_config));
	dat &= ~(MAC_CMDCFG_TX_ENA | MAC_CMDCFG_RX_ENA);
	dat |= MAC_CMDCFG_SW_RESET | MAC_CMDCFG_CNT_RESET;
	csrwr32(dat, priv->mac_dev, tse_csroffs(command_config));

	counter = 0;
	while (counter++ < ALTERA_TSE_SW_RESET_WATCHDOG_CNTR) {
		if (tse_bit_is_clear(priv->mac_dev, tse_csroffs(command_config),
				     MAC_CMDCFG_SW_RESET))
			break;
		udelay(1);
	}

	if (counter >= ALTERA_TSE_SW_RESET_WATCHDOG_CNTR) {
		dat = csrrd32(priv->mac_dev, tse_csroffs(command_config));
		dat &= ~MAC_CMDCFG_SW_RESET;
		csrwr32(dat, priv->mac_dev, tse_csroffs(command_config));
		return -1;
	}
	return 0;
}