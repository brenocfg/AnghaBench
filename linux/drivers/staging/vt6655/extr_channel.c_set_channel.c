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
struct vnt_private {scalar_t__ byBBVGACurrent; scalar_t__* abyBBVGA; scalar_t__ byRFType; scalar_t__ byLocalID; scalar_t__ byBBType; int /*<<< orphan*/  byCurrentCh; int /*<<< orphan*/  lock; scalar_t__ PortOffset; int /*<<< orphan*/  byCurPwr; scalar_t__ bEnablePSMode; scalar_t__ bUpdateBBVGA; } ;
struct ieee80211_channel {int /*<<< orphan*/  hw_value; } ;

/* Variables and functions */
 scalar_t__ BB_TYPE_11B ; 
 int /*<<< orphan*/  BBvSetVGAGainOffset (struct vnt_private*,scalar_t__) ; 
 int /*<<< orphan*/  BBvSoftwareReset (struct vnt_private*) ; 
 int /*<<< orphan*/  MACCR_CLRNAV ; 
 int /*<<< orphan*/  MAC_REG_MACCR ; 
 scalar_t__ MAC_REG_PWRCCK ; 
 scalar_t__ MAC_REG_PWROFDM ; 
 int /*<<< orphan*/  MACvRegBitsOn (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvSelectPage0 (scalar_t__) ; 
 int /*<<< orphan*/  MACvSelectPage1 (scalar_t__) ; 
 int /*<<< orphan*/  RATE_1M ; 
 int /*<<< orphan*/  RATE_6M ; 
 scalar_t__ REV_ID_VT3253_B1 ; 
 scalar_t__ RF_AIROHA7230 ; 
 int /*<<< orphan*/  RFbAL7230SelectChannelPostProcess (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RFbSelectChannel (struct vnt_private*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFbSetPower (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFvWriteWakeProgSyn (struct vnt_private*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VNSvOutPortB (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool set_channel(struct vnt_private *priv, struct ieee80211_channel *ch)
{
	bool ret = true;

	if (priv->byCurrentCh == ch->hw_value)
		return ret;

	/* Set VGA to max sensitivity */
	if (priv->bUpdateBBVGA &&
	    priv->byBBVGACurrent != priv->abyBBVGA[0]) {
		priv->byBBVGACurrent = priv->abyBBVGA[0];

		BBvSetVGAGainOffset(priv, priv->byBBVGACurrent);
	}

	/* clear NAV */
	MACvRegBitsOn(priv->PortOffset, MAC_REG_MACCR, MACCR_CLRNAV);

	/* TX_PE will reserve 3 us for MAX2829 A mode only,
	 * it is for better TX throughput
	 */

	if (priv->byRFType == RF_AIROHA7230)
		RFbAL7230SelectChannelPostProcess(priv, priv->byCurrentCh,
						  ch->hw_value);

	priv->byCurrentCh = ch->hw_value;
	ret &= RFbSelectChannel(priv, priv->byRFType,
				ch->hw_value);

	/* Init Synthesizer Table */
	if (priv->bEnablePSMode)
		RFvWriteWakeProgSyn(priv, priv->byRFType, ch->hw_value);

	BBvSoftwareReset(priv);

	if (priv->byLocalID > REV_ID_VT3253_B1) {
		unsigned long flags;

		spin_lock_irqsave(&priv->lock, flags);

		/* set HW default power register */
		MACvSelectPage1(priv->PortOffset);
		RFbSetPower(priv, RATE_1M, priv->byCurrentCh);
		VNSvOutPortB(priv->PortOffset + MAC_REG_PWRCCK,
			     priv->byCurPwr);
		RFbSetPower(priv, RATE_6M, priv->byCurrentCh);
		VNSvOutPortB(priv->PortOffset + MAC_REG_PWROFDM,
			     priv->byCurPwr);
		MACvSelectPage0(priv->PortOffset);

		spin_unlock_irqrestore(&priv->lock, flags);
	}

	if (priv->byBBType == BB_TYPE_11B)
		RFbSetPower(priv, RATE_1M, priv->byCurrentCh);
	else
		RFbSetPower(priv, RATE_6M, priv->byCurrentCh);

	return ret;
}