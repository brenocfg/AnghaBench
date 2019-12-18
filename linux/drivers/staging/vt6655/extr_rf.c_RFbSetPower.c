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
typedef  int u16 ;
struct vnt_private {scalar_t__ dwDiagRefCount; unsigned char* abyCCKPwrTbl; unsigned char* abyOFDMPwrTbl; unsigned char byMaxPwrLevel; unsigned char byCurPwr; int /*<<< orphan*/  byRFType; } ;

/* Variables and functions */
 int CB_MAX_CHANNEL ; 
 int CB_MAX_CHANNEL_24G ; 
#define  RATE_11M 139 
#define  RATE_12M 138 
#define  RATE_18M 137 
#define  RATE_1M 136 
#define  RATE_24M 135 
#define  RATE_2M 134 
#define  RATE_36M 133 
#define  RATE_48M 132 
#define  RATE_54M 131 
#define  RATE_5M 130 
#define  RATE_6M 129 
#define  RATE_9M 128 
 int /*<<< orphan*/  RF_UW2452 ; 
 int RFbRawSetPower (struct vnt_private*,unsigned char,unsigned int) ; 

bool RFbSetPower(struct vnt_private *priv, unsigned int rate, u16 uCH)
{
	bool ret = true;
	unsigned char byPwr = 0;
	unsigned char byDec = 0;

	if (priv->dwDiagRefCount != 0)
		return true;

	if ((uCH < 1) || (uCH > CB_MAX_CHANNEL))
		return false;

	switch (rate) {
	case RATE_1M:
	case RATE_2M:
	case RATE_5M:
	case RATE_11M:
		if (uCH > CB_MAX_CHANNEL_24G)
			return false;

		byPwr = priv->abyCCKPwrTbl[uCH];
		break;
	case RATE_6M:
	case RATE_9M:
	case RATE_12M:
	case RATE_18M:
		byPwr = priv->abyOFDMPwrTbl[uCH];
		if (priv->byRFType == RF_UW2452)
			byDec = byPwr + 14;
		else
			byDec = byPwr + 10;

		if (byDec >= priv->byMaxPwrLevel)
			byDec = priv->byMaxPwrLevel - 1;

		byPwr = byDec;
		break;
	case RATE_24M:
	case RATE_36M:
	case RATE_48M:
	case RATE_54M:
		byPwr = priv->abyOFDMPwrTbl[uCH];
		break;
	}

	if (priv->byCurPwr == byPwr)
		return true;

	ret = RFbRawSetPower(priv, byPwr, rate);
	if (ret)
		priv->byCurPwr = byPwr;

	return ret;
}