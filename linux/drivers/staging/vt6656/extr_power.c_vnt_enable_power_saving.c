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
typedef  int u16 ;
struct vnt_private {int current_aid; scalar_t__ op_mode; TYPE_1__* usb; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int C_PWBT ; 
 int /*<<< orphan*/  MAC_REG_AIDATIM ; 
 int /*<<< orphan*/  MAC_REG_PSCFG ; 
 int /*<<< orphan*/  MAC_REG_PSCTL ; 
 int /*<<< orphan*/  MAC_REG_PWBT ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  PSCFG_AUTOSLEEP ; 
 int /*<<< orphan*/  PSCTL_ALBCN ; 
 int /*<<< orphan*/  PSCTL_GO2DOZE ; 
 int /*<<< orphan*/  PSCTL_LNBCN ; 
 int /*<<< orphan*/  PSCTL_PSEN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vnt_mac_reg_bits_off (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_mac_reg_bits_on (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_mac_write_word (struct vnt_private*,int /*<<< orphan*/ ,int) ; 

void vnt_enable_power_saving(struct vnt_private *priv, u16 listen_interval)
{
	u16 aid = priv->current_aid | BIT(14) | BIT(15);

	/* set period of power up before TBTT */
	vnt_mac_write_word(priv, MAC_REG_PWBT, C_PWBT);

	if (priv->op_mode != NL80211_IFTYPE_ADHOC)
		/* set AID */
		vnt_mac_write_word(priv, MAC_REG_AIDATIM, aid);

	/* Warren:06-18-2004,the sequence must follow
	 * PSEN->AUTOSLEEP->GO2DOZE
	 */
	/* enable power saving hw function */
	vnt_mac_reg_bits_on(priv, MAC_REG_PSCTL, PSCTL_PSEN);

	/* Set AutoSleep */
	vnt_mac_reg_bits_on(priv, MAC_REG_PSCFG, PSCFG_AUTOSLEEP);

	/* Warren:MUST turn on this once before turn on AUTOSLEEP ,or the
	 * AUTOSLEEP doesn't work
	 */
	vnt_mac_reg_bits_on(priv, MAC_REG_PSCTL, PSCTL_GO2DOZE);

	if (listen_interval >= 2) {
		/* clear always listen beacon */
		vnt_mac_reg_bits_off(priv, MAC_REG_PSCTL, PSCTL_ALBCN);

		/* first time set listen next beacon */
		vnt_mac_reg_bits_on(priv, MAC_REG_PSCTL, PSCTL_LNBCN);
	} else {
		/* always listen beacon */
		vnt_mac_reg_bits_on(priv, MAC_REG_PSCTL, PSCTL_ALBCN);
	}

	dev_dbg(&priv->usb->dev,  "PS:Power Saving Mode Enable...\n");
}