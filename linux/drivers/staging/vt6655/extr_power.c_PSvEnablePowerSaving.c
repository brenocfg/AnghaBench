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
struct vnt_private {int current_aid; scalar_t__ op_mode; int bEnablePSMode; int bPWBitOn; scalar_t__ PortOffset; } ;
struct TYPE_2__ {int /*<<< orphan*/  wCurrATIMWindow; } ;

/* Variables and functions */
 int BIT (int) ; 
 int C_PWBT ; 
 scalar_t__ MAC_REG_AIDATIM ; 
 int /*<<< orphan*/  MAC_REG_PSCFG ; 
 int /*<<< orphan*/  MAC_REG_PSCTL ; 
 scalar_t__ MAC_REG_PWBT ; 
 int /*<<< orphan*/  MAC_REG_TFTCTL ; 
 int /*<<< orphan*/  MACvRegBitsOff (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvRegBitsOn (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvWriteATIMW (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  PSCFG_AUTOSLEEP ; 
 int /*<<< orphan*/  PSCTL_ALBCN ; 
 int /*<<< orphan*/  PSCTL_LNBCN ; 
 int /*<<< orphan*/  PSCTL_PSEN ; 
 int /*<<< orphan*/  TFTCTL_HWUTSF ; 
 int /*<<< orphan*/  VNSvOutPortW (scalar_t__,int) ; 
 TYPE_1__* pMgmt ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

void PSvEnablePowerSaving(struct vnt_private *priv,
			  unsigned short wListenInterval)
{
	u16 wAID = priv->current_aid | BIT(14) | BIT(15);

	/* set period of power up before TBTT */
	VNSvOutPortW(priv->PortOffset + MAC_REG_PWBT, C_PWBT);
	if (priv->op_mode != NL80211_IFTYPE_ADHOC) {
		/* set AID */
		VNSvOutPortW(priv->PortOffset + MAC_REG_AIDATIM, wAID);
	} else {
		/* set ATIM Window */
#if 0 /* TODO atim window */
		MACvWriteATIMW(priv->PortOffset, pMgmt->wCurrATIMWindow);
#endif
	}
	/* Set AutoSleep */
	MACvRegBitsOn(priv->PortOffset, MAC_REG_PSCFG, PSCFG_AUTOSLEEP);
	/* Set HWUTSF */
	MACvRegBitsOn(priv->PortOffset, MAC_REG_TFTCTL, TFTCTL_HWUTSF);

	if (wListenInterval >= 2) {
		/* clear always listen beacon */
		MACvRegBitsOff(priv->PortOffset, MAC_REG_PSCTL, PSCTL_ALBCN);
		/* first time set listen next beacon */
		MACvRegBitsOn(priv->PortOffset, MAC_REG_PSCTL, PSCTL_LNBCN);
	} else {
		/* always listen beacon */
		MACvRegBitsOn(priv->PortOffset, MAC_REG_PSCTL, PSCTL_ALBCN);
	}

	/* enable power saving hw function */
	MACvRegBitsOn(priv->PortOffset, MAC_REG_PSCTL, PSCTL_PSEN);
	priv->bEnablePSMode = true;

	priv->bPWBitOn = true;
	pr_debug("PS:Power Saving Mode Enable...\n");
}