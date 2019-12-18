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
struct vnt_private {int /*<<< orphan*/  uSIFS; int /*<<< orphan*/  byTopOFDMBasicRate; int /*<<< orphan*/  byPreambleType; int /*<<< orphan*/  byTopCCKBasicRate; } ;

/* Variables and functions */
 unsigned char AUTO_FB_0 ; 
 unsigned int BBuGetFrameTime (int /*<<< orphan*/ ,unsigned char,int,int /*<<< orphan*/ ) ; 
#define  DATADUR_A 131 
#define  DATADUR_A_F0 130 
#define  DATADUR_A_F1 129 
#define  DATADUR_B 128 
 size_t FB_RATE0 ; 
 size_t FB_RATE1 ; 
 unsigned short RATE_18M ; 
 unsigned short RATE_54M ; 
 unsigned int s_uGetTxRsvTime (struct vnt_private*,unsigned char,unsigned int,unsigned short,int) ; 
 unsigned short** wFB_Opt0 ; 
 unsigned short** wFB_Opt1 ; 

__attribute__((used)) static
unsigned int
s_uGetDataDuration(
	struct vnt_private *pDevice,
	unsigned char byDurType,
	unsigned int cbFrameLength,
	unsigned char byPktType,
	unsigned short wRate,
	bool bNeedAck,
	unsigned int uFragIdx,
	unsigned int cbLastFragmentSize,
	unsigned int uMACfragNum,
	unsigned char byFBOption
)
{
	bool bLastFrag = false;
	unsigned int uAckTime = 0, uNextPktTime = 0;

	if (uFragIdx == (uMACfragNum - 1))
		bLastFrag = true;

	switch (byDurType) {
	case DATADUR_B:    /* DATADUR_B */
		if (((uMACfragNum == 1)) || bLastFrag) {/* Non Frag or Last Frag */
			if (bNeedAck) {
				uAckTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, 14, pDevice->byTopCCKBasicRate);
				return pDevice->uSIFS + uAckTime;
			} else {
				return 0;
			}
		} else {/* First Frag or Mid Frag */
			if (uFragIdx == (uMACfragNum - 2))
				uNextPktTime = s_uGetTxRsvTime(pDevice, byPktType, cbLastFragmentSize, wRate, bNeedAck);
			else
				uNextPktTime = s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wRate, bNeedAck);

			if (bNeedAck) {
				uAckTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, 14, pDevice->byTopCCKBasicRate);
				return pDevice->uSIFS + uAckTime + uNextPktTime;
			} else {
				return pDevice->uSIFS + uNextPktTime;
			}
		}
		break;

	case DATADUR_A:    /* DATADUR_A */
		if (((uMACfragNum == 1)) || bLastFrag) {/* Non Frag or Last Frag */
			if (bNeedAck) {
				uAckTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, 14, pDevice->byTopOFDMBasicRate);
				return pDevice->uSIFS + uAckTime;
			} else {
				return 0;
			}
		} else {/* First Frag or Mid Frag */
			if (uFragIdx == (uMACfragNum - 2))
				uNextPktTime = s_uGetTxRsvTime(pDevice, byPktType, cbLastFragmentSize, wRate, bNeedAck);
			else
				uNextPktTime = s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wRate, bNeedAck);

			if (bNeedAck) {
				uAckTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, 14, pDevice->byTopOFDMBasicRate);
				return pDevice->uSIFS + uAckTime + uNextPktTime;
			} else {
				return pDevice->uSIFS + uNextPktTime;
			}
		}
		break;

	case DATADUR_A_F0:    /* DATADUR_A_F0 */
		if (((uMACfragNum == 1)) || bLastFrag) {/* Non Frag or Last Frag */
			if (bNeedAck) {
				uAckTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, 14, pDevice->byTopOFDMBasicRate);
				return pDevice->uSIFS + uAckTime;
			} else {
				return 0;
			}
		} else { /* First Frag or Mid Frag */
			if (byFBOption == AUTO_FB_0) {
				if (wRate < RATE_18M)
					wRate = RATE_18M;
				else if (wRate > RATE_54M)
					wRate = RATE_54M;

				if (uFragIdx == (uMACfragNum - 2))
					uNextPktTime = s_uGetTxRsvTime(pDevice, byPktType, cbLastFragmentSize, wFB_Opt0[FB_RATE0][wRate-RATE_18M], bNeedAck);
				else
					uNextPktTime = s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wFB_Opt0[FB_RATE0][wRate-RATE_18M], bNeedAck);

			} else { /* (byFBOption == AUTO_FB_1) */
				if (wRate < RATE_18M)
					wRate = RATE_18M;
				else if (wRate > RATE_54M)
					wRate = RATE_54M;

				if (uFragIdx == (uMACfragNum - 2))
					uNextPktTime = s_uGetTxRsvTime(pDevice, byPktType, cbLastFragmentSize, wFB_Opt1[FB_RATE0][wRate-RATE_18M], bNeedAck);
				else
					uNextPktTime = s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wFB_Opt1[FB_RATE0][wRate-RATE_18M], bNeedAck);
			}

			if (bNeedAck) {
				uAckTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, 14, pDevice->byTopOFDMBasicRate);
				return pDevice->uSIFS + uAckTime + uNextPktTime;
			} else {
				return pDevice->uSIFS + uNextPktTime;
			}
		}
		break;

	case DATADUR_A_F1:    /* DATADUR_A_F1 */
		if (((uMACfragNum == 1)) || bLastFrag) { /* Non Frag or Last Frag */
			if (bNeedAck) {
				uAckTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, 14, pDevice->byTopOFDMBasicRate);
				return pDevice->uSIFS + uAckTime;
			} else {
				return 0;
			}
		} else { /* First Frag or Mid Frag */
			if (byFBOption == AUTO_FB_0) {
				if (wRate < RATE_18M)
					wRate = RATE_18M;
				else if (wRate > RATE_54M)
					wRate = RATE_54M;

				if (uFragIdx == (uMACfragNum - 2))
					uNextPktTime = s_uGetTxRsvTime(pDevice, byPktType, cbLastFragmentSize, wFB_Opt0[FB_RATE1][wRate-RATE_18M], bNeedAck);
				else
					uNextPktTime = s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wFB_Opt0[FB_RATE1][wRate-RATE_18M], bNeedAck);

			} else { /* (byFBOption == AUTO_FB_1) */
				if (wRate < RATE_18M)
					wRate = RATE_18M;
				else if (wRate > RATE_54M)
					wRate = RATE_54M;

				if (uFragIdx == (uMACfragNum - 2))
					uNextPktTime = s_uGetTxRsvTime(pDevice, byPktType, cbLastFragmentSize, wFB_Opt1[FB_RATE1][wRate-RATE_18M], bNeedAck);
				else
					uNextPktTime = s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wFB_Opt1[FB_RATE1][wRate-RATE_18M], bNeedAck);
			}
			if (bNeedAck) {
				uAckTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, 14, pDevice->byTopOFDMBasicRate);
				return pDevice->uSIFS + uAckTime + uNextPktTime;
			} else {
				return pDevice->uSIFS + uNextPktTime;
			}
		}
		break;

	default:
		break;
	}

	return 0;
}