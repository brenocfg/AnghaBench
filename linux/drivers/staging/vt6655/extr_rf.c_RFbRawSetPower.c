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
struct vnt_private {unsigned char byMaxPwrLevel; int byRFType; } ;

/* Variables and functions */
 int BY_AL2230_REG_LEN ; 
 int BY_AL7230_REG_LEN ; 
 int IFREGCTL_REGW ; 
 int IFRFbWriteEmbedded (struct vnt_private*,unsigned long) ; 
 unsigned int RATE_11M ; 
#define  RF_AIROHA 130 
#define  RF_AIROHA7230 129 
#define  RF_AL2230S 128 
 unsigned long* dwAL2230PowerTable ; 

bool RFbRawSetPower(struct vnt_private *priv, unsigned char byPwr,
		    unsigned int rate)
{
	bool ret = true;
	unsigned long dwMax7230Pwr = 0;

	if (byPwr >=  priv->byMaxPwrLevel)
		return false;

	switch (priv->byRFType) {
	case RF_AIROHA:
		ret &= IFRFbWriteEmbedded(priv, dwAL2230PowerTable[byPwr]);
		if (rate <= RATE_11M)
			ret &= IFRFbWriteEmbedded(priv, 0x0001B400 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW);
		else
			ret &= IFRFbWriteEmbedded(priv, 0x0005A400 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW);

		break;

	case RF_AL2230S:
		ret &= IFRFbWriteEmbedded(priv, dwAL2230PowerTable[byPwr]);
		if (rate <= RATE_11M) {
			ret &= IFRFbWriteEmbedded(priv, 0x040C1400 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW);
			ret &= IFRFbWriteEmbedded(priv, 0x00299B00 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW);
		} else {
			ret &= IFRFbWriteEmbedded(priv, 0x0005A400 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW);
			ret &= IFRFbWriteEmbedded(priv, 0x00099B00 + (BY_AL2230_REG_LEN << 3) + IFREGCTL_REGW);
		}

		break;

	case RF_AIROHA7230:
		/* 0x080F1B00 for 3 wire control TxGain(D10)
		 * and 0x31 as TX Gain value
		 */
		dwMax7230Pwr = 0x080C0B00 | ((byPwr) << 12) |
			(BY_AL7230_REG_LEN << 3)  | IFREGCTL_REGW;

		ret &= IFRFbWriteEmbedded(priv, dwMax7230Pwr);
		break;

	default:
		break;
	}
	return ret;
}