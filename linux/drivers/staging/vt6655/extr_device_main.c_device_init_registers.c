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
struct vnt_private {int bAES; int bProtectMode; int bNonERPPresent; int bBarkerPreambleMd; scalar_t__ byLocalID; int byMinChannel; int bTxRxAntInv; int byAntennaCount; int dwTxAntennaSel; int dwRxAntennaSel; int byCurPwr; unsigned char* abyCCKDefaultPwr; unsigned char* abyOFDMDefaultPwr; int bRadioOff; int byRadioCtl; int bHWRadioOff; int byGPIO; scalar_t__ PortOffset; int /*<<< orphan*/  abyCurrentNetAddr; scalar_t__ bRadioControlOff; void* wCurrentRate; void* byTxAntennaMode; void* byRxAntennaMode; int /*<<< orphan*/ * abyBBVGA; int /*<<< orphan*/  byBBVGACurrent; int /*<<< orphan*/  byBBVGANew; scalar_t__ bUpdateBBVGA; int /*<<< orphan*/  byLongRetryLimit; int /*<<< orphan*/  byShortRetryLimit; void** abyOFDMPwrTbl; void** abyCCKPwrTbl; void* byOFDMPwrG; void* byCCKPwr; int /*<<< orphan*/  byZoneType; int /*<<< orphan*/ * abyEEPROM; int /*<<< orphan*/  bZoneRegExist; int /*<<< orphan*/  byOriginalZonetype; int /*<<< orphan*/  byMaxChannel; int /*<<< orphan*/  lock; void* byTopCCKBasicRate; int /*<<< orphan*/  byTopOFDMBasicRate; } ;

/* Variables and functions */
 void* ANT_A ; 
 void* ANT_B ; 
 int /*<<< orphan*/  BBbVT3253Init (struct vnt_private*) ; 
 int /*<<< orphan*/  BBvSetRxAntennaMode (struct vnt_private*,void*) ; 
 int /*<<< orphan*/  BBvSetTxAntennaMode (struct vnt_private*,void*) ; 
 int /*<<< orphan*/  BBvSetVGAGainOffset (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BBvSoftwareReset (struct vnt_private*) ; 
 int /*<<< orphan*/  CARDbRadioPowerOff (struct vnt_private*) ; 
 int /*<<< orphan*/  CARDvSafeResetRx (struct vnt_private*) ; 
 int /*<<< orphan*/  CARDvSafeResetTx (struct vnt_private*) ; 
 int /*<<< orphan*/  CB_MAX_CHANNEL ; 
 unsigned int CB_MAX_CHANNEL_24G ; 
 unsigned int CB_MAX_CHANNEL_5G ; 
 int CFG_NOTXTIMEOUT ; 
 int CFG_TKIPOPT ; 
 unsigned char EEP_ANTENNA_AUX ; 
 unsigned char EEP_ANTENNA_MAIN ; 
 unsigned char EEP_ANTINV ; 
 unsigned char EEP_OFS_ANTENNA ; 
 scalar_t__ EEP_OFS_CCK_PWR_TBL ; 
 scalar_t__ EEP_OFS_OFDMA_PWR_TBL ; 
 scalar_t__ EEP_OFS_OFDMA_PWR_dBm ; 
 scalar_t__ EEP_OFS_OFDM_PWR_TBL ; 
 unsigned char EEP_OFS_PWR_CCK ; 
 unsigned char EEP_OFS_PWR_OFDMG ; 
 unsigned char EEP_OFS_RADIOCTL ; 
 size_t EEP_OFS_ZONETYPE ; 
 int EEP_RADIOCTL_ENABLE ; 
 int EEP_RADIOCTL_INV ; 
 int GPIO0_DATA ; 
 int /*<<< orphan*/  MAC_REG_CFG ; 
 scalar_t__ MAC_REG_LOCALID ; 
 scalar_t__ MAC_REG_MSRCTL ; 
 int /*<<< orphan*/  MAC_REG_RCR ; 
 scalar_t__ MAC_REG_TFTCTL ; 
 int /*<<< orphan*/  MACbShutdown (struct vnt_private*) ; 
 int /*<<< orphan*/  MACbSoftwareReset (struct vnt_private*) ; 
 int /*<<< orphan*/  MACvGPIOIn (scalar_t__,int*) ; 
 int /*<<< orphan*/  MACvInitialize (struct vnt_private*) ; 
 int /*<<< orphan*/  MACvReceive0 (scalar_t__) ; 
 int /*<<< orphan*/  MACvReceive1 (scalar_t__) ; 
 int /*<<< orphan*/  MACvRegBitsOn (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvSelectPage0 (scalar_t__) ; 
 int /*<<< orphan*/  MACvSelectPage1 (scalar_t__) ; 
 int /*<<< orphan*/  MACvSetLongRetryLimit (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvSetShortRetryLimit (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvStart (scalar_t__) ; 
 int /*<<< orphan*/  MACvWordRegBitsOn (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int MSRCTL1_CSAPAREN ; 
 int MSRCTL1_TXPWR ; 
 void* RATE_1M ; 
 int /*<<< orphan*/  RATE_24M ; 
 void* RATE_54M ; 
 int /*<<< orphan*/  RCR_WPAERR ; 
 scalar_t__ REV_ID_VT3253_A1 ; 
 scalar_t__ REV_ID_VT3253_B1 ; 
 int /*<<< orphan*/  RFbInit (struct vnt_private*) ; 
 void* SROMbyReadEmbedded (scalar_t__,unsigned char) ; 
 int /*<<< orphan*/  SROMvReadAllContents (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SROMvReadEtherAddress (scalar_t__,int /*<<< orphan*/ ) ; 
 int TFTCTL_TSFCNTREN ; 
 int TFTCTL_TSFCNTRST ; 
 int /*<<< orphan*/  VNSvInPortB (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  VNSvOutPortB (scalar_t__,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void device_init_registers(struct vnt_private *priv)
{
	unsigned long flags;
	unsigned int ii;
	unsigned char byValue;
	unsigned char byCCKPwrdBm = 0;
	unsigned char byOFDMPwrdBm = 0;

	MACbShutdown(priv);
	BBvSoftwareReset(priv);

	/* Do MACbSoftwareReset in MACvInitialize */
	MACbSoftwareReset(priv);

	priv->bAES = false;

	/* Only used in 11g type, sync with ERP IE */
	priv->bProtectMode = false;

	priv->bNonERPPresent = false;
	priv->bBarkerPreambleMd = false;
	priv->wCurrentRate = RATE_1M;
	priv->byTopOFDMBasicRate = RATE_24M;
	priv->byTopCCKBasicRate = RATE_1M;

	/* init MAC */
	MACvInitialize(priv);

	/* Get Local ID */
	VNSvInPortB(priv->PortOffset + MAC_REG_LOCALID, &priv->byLocalID);

	spin_lock_irqsave(&priv->lock, flags);

	SROMvReadAllContents(priv->PortOffset, priv->abyEEPROM);

	spin_unlock_irqrestore(&priv->lock, flags);

	/* Get Channel range */
	priv->byMinChannel = 1;
	priv->byMaxChannel = CB_MAX_CHANNEL;

	/* Get Antena */
	byValue = SROMbyReadEmbedded(priv->PortOffset, EEP_OFS_ANTENNA);
	if (byValue & EEP_ANTINV)
		priv->bTxRxAntInv = true;
	else
		priv->bTxRxAntInv = false;

	byValue &= (EEP_ANTENNA_AUX | EEP_ANTENNA_MAIN);
	/* if not set default is All */
	if (byValue == 0)
		byValue = (EEP_ANTENNA_AUX | EEP_ANTENNA_MAIN);

	if (byValue == (EEP_ANTENNA_AUX | EEP_ANTENNA_MAIN)) {
		priv->byAntennaCount = 2;
		priv->byTxAntennaMode = ANT_B;
		priv->dwTxAntennaSel = 1;
		priv->dwRxAntennaSel = 1;

		if (priv->bTxRxAntInv)
			priv->byRxAntennaMode = ANT_A;
		else
			priv->byRxAntennaMode = ANT_B;
	} else  {
		priv->byAntennaCount = 1;
		priv->dwTxAntennaSel = 0;
		priv->dwRxAntennaSel = 0;

		if (byValue & EEP_ANTENNA_AUX) {
			priv->byTxAntennaMode = ANT_A;

			if (priv->bTxRxAntInv)
				priv->byRxAntennaMode = ANT_B;
			else
				priv->byRxAntennaMode = ANT_A;
		} else {
			priv->byTxAntennaMode = ANT_B;

			if (priv->bTxRxAntInv)
				priv->byRxAntennaMode = ANT_A;
			else
				priv->byRxAntennaMode = ANT_B;
		}
	}

	/* Set initial antenna mode */
	BBvSetTxAntennaMode(priv, priv->byTxAntennaMode);
	BBvSetRxAntennaMode(priv, priv->byRxAntennaMode);

	/* zonetype initial */
	priv->byOriginalZonetype = priv->abyEEPROM[EEP_OFS_ZONETYPE];

	if (!priv->bZoneRegExist)
		priv->byZoneType = priv->abyEEPROM[EEP_OFS_ZONETYPE];

	pr_debug("priv->byZoneType = %x\n", priv->byZoneType);

	/* Init RF module */
	RFbInit(priv);

	/* Get Desire Power Value */
	priv->byCurPwr = 0xFF;
	priv->byCCKPwr = SROMbyReadEmbedded(priv->PortOffset, EEP_OFS_PWR_CCK);
	priv->byOFDMPwrG = SROMbyReadEmbedded(priv->PortOffset, EEP_OFS_PWR_OFDMG);

	/* Load power Table */
	for (ii = 0; ii < CB_MAX_CHANNEL_24G; ii++) {
		priv->abyCCKPwrTbl[ii + 1] =
			SROMbyReadEmbedded(priv->PortOffset,
					   (unsigned char)(ii + EEP_OFS_CCK_PWR_TBL));
		if (priv->abyCCKPwrTbl[ii + 1] == 0)
			priv->abyCCKPwrTbl[ii + 1] = priv->byCCKPwr;

		priv->abyOFDMPwrTbl[ii + 1] =
			SROMbyReadEmbedded(priv->PortOffset,
					   (unsigned char)(ii + EEP_OFS_OFDM_PWR_TBL));
		if (priv->abyOFDMPwrTbl[ii + 1] == 0)
			priv->abyOFDMPwrTbl[ii + 1] = priv->byOFDMPwrG;

		priv->abyCCKDefaultPwr[ii + 1] = byCCKPwrdBm;
		priv->abyOFDMDefaultPwr[ii + 1] = byOFDMPwrdBm;
	}

	/* recover 12,13 ,14channel for EUROPE by 11 channel */
	for (ii = 11; ii < 14; ii++) {
		priv->abyCCKPwrTbl[ii] = priv->abyCCKPwrTbl[10];
		priv->abyOFDMPwrTbl[ii] = priv->abyOFDMPwrTbl[10];
	}

	/* Load OFDM A Power Table */
	for (ii = 0; ii < CB_MAX_CHANNEL_5G; ii++) {
		priv->abyOFDMPwrTbl[ii + CB_MAX_CHANNEL_24G + 1] =
			SROMbyReadEmbedded(priv->PortOffset,
					   (unsigned char)(ii + EEP_OFS_OFDMA_PWR_TBL));

		priv->abyOFDMDefaultPwr[ii + CB_MAX_CHANNEL_24G + 1] =
			SROMbyReadEmbedded(priv->PortOffset,
					   (unsigned char)(ii + EEP_OFS_OFDMA_PWR_dBm));
	}

	if (priv->byLocalID > REV_ID_VT3253_B1) {
		MACvSelectPage1(priv->PortOffset);

		VNSvOutPortB(priv->PortOffset + MAC_REG_MSRCTL + 1,
			     (MSRCTL1_TXPWR | MSRCTL1_CSAPAREN));

		MACvSelectPage0(priv->PortOffset);
	}

	/* use relative tx timeout and 802.11i D4 */
	MACvWordRegBitsOn(priv->PortOffset,
			  MAC_REG_CFG, (CFG_TKIPOPT | CFG_NOTXTIMEOUT));

	/* set performance parameter by registry */
	MACvSetShortRetryLimit(priv, priv->byShortRetryLimit);
	MACvSetLongRetryLimit(priv, priv->byLongRetryLimit);

	/* reset TSF counter */
	VNSvOutPortB(priv->PortOffset + MAC_REG_TFTCTL, TFTCTL_TSFCNTRST);
	/* enable TSF counter */
	VNSvOutPortB(priv->PortOffset + MAC_REG_TFTCTL, TFTCTL_TSFCNTREN);

	/* initialize BBP registers */
	BBbVT3253Init(priv);

	if (priv->bUpdateBBVGA) {
		priv->byBBVGACurrent = priv->abyBBVGA[0];
		priv->byBBVGANew = priv->byBBVGACurrent;
		BBvSetVGAGainOffset(priv, priv->abyBBVGA[0]);
	}

	BBvSetRxAntennaMode(priv, priv->byRxAntennaMode);
	BBvSetTxAntennaMode(priv, priv->byTxAntennaMode);

	/* Set BB and packet type at the same time. */
	/* Set Short Slot Time, xIFS, and RSPINF. */
	priv->wCurrentRate = RATE_54M;

	priv->bRadioOff = false;

	priv->byRadioCtl = SROMbyReadEmbedded(priv->PortOffset,
						 EEP_OFS_RADIOCTL);
	priv->bHWRadioOff = false;

	if (priv->byRadioCtl & EEP_RADIOCTL_ENABLE) {
		/* Get GPIO */
		MACvGPIOIn(priv->PortOffset, &priv->byGPIO);

		if (((priv->byGPIO & GPIO0_DATA) &&
		     !(priv->byRadioCtl & EEP_RADIOCTL_INV)) ||
		     (!(priv->byGPIO & GPIO0_DATA) &&
		     (priv->byRadioCtl & EEP_RADIOCTL_INV)))
			priv->bHWRadioOff = true;
	}

	if (priv->bHWRadioOff || priv->bRadioControlOff)
		CARDbRadioPowerOff(priv);

	/* get Permanent network address */
	SROMvReadEtherAddress(priv->PortOffset, priv->abyCurrentNetAddr);
	pr_debug("Network address = %pM\n", priv->abyCurrentNetAddr);

	/* reset Tx pointer */
	CARDvSafeResetRx(priv);
	/* reset Rx pointer */
	CARDvSafeResetTx(priv);

	if (priv->byLocalID <= REV_ID_VT3253_A1)
		MACvRegBitsOn(priv->PortOffset, MAC_REG_RCR, RCR_WPAERR);

	/* Turn On Rx DMA */
	MACvReceive0(priv->PortOffset);
	MACvReceive1(priv->PortOffset);

	/* start the adapter */
	MACvStart(priv->PortOffset);
}