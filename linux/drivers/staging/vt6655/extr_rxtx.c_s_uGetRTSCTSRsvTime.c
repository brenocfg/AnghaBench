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
typedef  int /*<<< orphan*/  u16 ;
struct vnt_private {unsigned short byTopCCKBasicRate; unsigned short byTopOFDMBasicRate; int uSIFS; int /*<<< orphan*/  byPreambleType; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 unsigned int BBuGetFrameTime (int /*<<< orphan*/ ,unsigned char,int,unsigned short) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
__le16
s_uGetRTSCTSRsvTime(
	struct vnt_private *pDevice,
	unsigned char byRTSRsvType,
	unsigned char byPktType,
	unsigned int cbFrameLength,
	unsigned short wCurrentRate
)
{
	unsigned int uRrvTime, uRTSTime, uCTSTime, uAckTime, uDataTime;

	uRrvTime = uRTSTime = uCTSTime = uAckTime = uDataTime = 0;

	uDataTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, cbFrameLength, wCurrentRate);
	if (byRTSRsvType == 0) { /* RTSTxRrvTime_bb */
		uRTSTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, 20, pDevice->byTopCCKBasicRate);
		uCTSTime = uAckTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, 14, pDevice->byTopCCKBasicRate);
	} else if (byRTSRsvType == 1) { /* RTSTxRrvTime_ba, only in 2.4GHZ */
		uRTSTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, 20, pDevice->byTopCCKBasicRate);
		uCTSTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, 14, pDevice->byTopCCKBasicRate);
		uAckTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, 14, pDevice->byTopOFDMBasicRate);
	} else if (byRTSRsvType == 2) { /* RTSTxRrvTime_aa */
		uRTSTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, 20, pDevice->byTopOFDMBasicRate);
		uCTSTime = uAckTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, 14, pDevice->byTopOFDMBasicRate);
	} else if (byRTSRsvType == 3) { /* CTSTxRrvTime_ba, only in 2.4GHZ */
		uCTSTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, 14, pDevice->byTopCCKBasicRate);
		uAckTime = BBuGetFrameTime(pDevice->byPreambleType, byPktType, 14, pDevice->byTopOFDMBasicRate);
		uRrvTime = uCTSTime + uAckTime + uDataTime + 2 * pDevice->uSIFS;
		return cpu_to_le16((u16)uRrvTime);
	}

	/* RTSRrvTime */
	uRrvTime = uRTSTime + uCTSTime + uAckTime + uDataTime + 3 * pDevice->uSIFS;
	return cpu_to_le16((u16)uRrvTime);
}