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
struct vnt_tx_fifo_head {int /*<<< orphan*/  current_rate; int /*<<< orphan*/  fifo_ctl; } ;
struct vnt_rrv_time_rts {void* rrv_time_b; void* rrv_time_a; void* rts_rrv_time_bb; void* rts_rrv_time_ba; void* rts_rrv_time_aa; } ;
struct vnt_rrv_time_cts {void* cts_rrv_time_ba; void* rrv_time_b; void* rrv_time_a; } ;
struct vnt_rrv_time_ab {void* rrv_time; void* rts_rrv_time; } ;
struct vnt_private {unsigned short byTopCCKBasicRate; } ;

/* Variables and functions */
 unsigned char AUTO_FB_0 ; 
 unsigned char AUTO_FB_1 ; 
 unsigned char AUTO_FB_NONE ; 
 int FIFOCTL_AUTO_FB_0 ; 
 int FIFOCTL_AUTO_FB_1 ; 
 int FIFOCTL_CRCDIS ; 
 unsigned char PK_TYPE_11A ; 
 unsigned char PK_TYPE_11B ; 
 unsigned char PK_TYPE_11GA ; 
 unsigned char PK_TYPE_11GB ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned short) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* s_uGetRTSCTSRsvTime (struct vnt_private*,int,unsigned char,unsigned int,unsigned short) ; 
 int /*<<< orphan*/  s_vFillCTSHead (struct vnt_private*,unsigned int,unsigned char,void*,unsigned int,int,int,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  s_vFillRTSHead (struct vnt_private*,unsigned char,void*,unsigned int,int,int,void*,unsigned short,unsigned char) ; 
 void* vnt_rxtx_rsvtime_le16 (struct vnt_private*,unsigned char,unsigned int,unsigned short,int) ; 

__attribute__((used)) static
void
s_vGenerateTxParameter(
	struct vnt_private *pDevice,
	unsigned char byPktType,
	struct vnt_tx_fifo_head *tx_buffer_head,
	void *pvRrvTime,
	void *pvRTS,
	void *pvCTS,
	unsigned int cbFrameSize,
	bool bNeedACK,
	unsigned int uDMAIdx,
	void *psEthHeader,
	unsigned short wCurrentRate
)
{
	u16 fifo_ctl = le16_to_cpu(tx_buffer_head->fifo_ctl);
	bool bDisCRC = false;
	unsigned char byFBOption = AUTO_FB_NONE;

	tx_buffer_head->current_rate = cpu_to_le16(wCurrentRate);

	if (fifo_ctl & FIFOCTL_CRCDIS)
		bDisCRC = true;

	if (fifo_ctl & FIFOCTL_AUTO_FB_0)
		byFBOption = AUTO_FB_0;
	else if (fifo_ctl & FIFOCTL_AUTO_FB_1)
		byFBOption = AUTO_FB_1;

	if (!pvRrvTime)
		return;

	if (byPktType == PK_TYPE_11GB || byPktType == PK_TYPE_11GA) {
		if (pvRTS) { /* RTS_need */
			/* Fill RsvTime */
			struct vnt_rrv_time_rts *buf = pvRrvTime;

			buf->rts_rrv_time_aa = s_uGetRTSCTSRsvTime(pDevice, 2, byPktType, cbFrameSize, wCurrentRate);
			buf->rts_rrv_time_ba = s_uGetRTSCTSRsvTime(pDevice, 1, byPktType, cbFrameSize, wCurrentRate);
			buf->rts_rrv_time_bb = s_uGetRTSCTSRsvTime(pDevice, 0, byPktType, cbFrameSize, wCurrentRate);
			buf->rrv_time_a = vnt_rxtx_rsvtime_le16(pDevice, byPktType, cbFrameSize, wCurrentRate, bNeedACK);
			buf->rrv_time_b = vnt_rxtx_rsvtime_le16(pDevice, PK_TYPE_11B, cbFrameSize, pDevice->byTopCCKBasicRate, bNeedACK);

			s_vFillRTSHead(pDevice, byPktType, pvRTS, cbFrameSize, bNeedACK, bDisCRC, psEthHeader, wCurrentRate, byFBOption);
		} else {/* RTS_needless, PCF mode */
			struct vnt_rrv_time_cts *buf = pvRrvTime;

			buf->rrv_time_a = vnt_rxtx_rsvtime_le16(pDevice, byPktType, cbFrameSize, wCurrentRate, bNeedACK);
			buf->rrv_time_b = vnt_rxtx_rsvtime_le16(pDevice, PK_TYPE_11B, cbFrameSize, pDevice->byTopCCKBasicRate, bNeedACK);
			buf->cts_rrv_time_ba = s_uGetRTSCTSRsvTime(pDevice, 3, byPktType, cbFrameSize, wCurrentRate);

			/* Fill CTS */
			s_vFillCTSHead(pDevice, uDMAIdx, byPktType, pvCTS, cbFrameSize, bNeedACK, bDisCRC, wCurrentRate, byFBOption);
		}
	} else if (byPktType == PK_TYPE_11A) {
		if (pvRTS) {/* RTS_need, non PCF mode */
			struct vnt_rrv_time_ab *buf = pvRrvTime;

			buf->rts_rrv_time = s_uGetRTSCTSRsvTime(pDevice, 2, byPktType, cbFrameSize, wCurrentRate);
			buf->rrv_time = vnt_rxtx_rsvtime_le16(pDevice, byPktType, cbFrameSize, wCurrentRate, bNeedACK);

			/* Fill RTS */
			s_vFillRTSHead(pDevice, byPktType, pvRTS, cbFrameSize, bNeedACK, bDisCRC, psEthHeader, wCurrentRate, byFBOption);
		} else if (!pvRTS) {/* RTS_needless, non PCF mode */
			struct vnt_rrv_time_ab *buf = pvRrvTime;

			buf->rrv_time = vnt_rxtx_rsvtime_le16(pDevice, PK_TYPE_11A, cbFrameSize, wCurrentRate, bNeedACK);
		}
	} else if (byPktType == PK_TYPE_11B) {
		if (pvRTS) {/* RTS_need, non PCF mode */
			struct vnt_rrv_time_ab *buf = pvRrvTime;

			buf->rts_rrv_time = s_uGetRTSCTSRsvTime(pDevice, 0, byPktType, cbFrameSize, wCurrentRate);
			buf->rrv_time = vnt_rxtx_rsvtime_le16(pDevice, PK_TYPE_11B, cbFrameSize, wCurrentRate, bNeedACK);

			/* Fill RTS */
			s_vFillRTSHead(pDevice, byPktType, pvRTS, cbFrameSize, bNeedACK, bDisCRC, psEthHeader, wCurrentRate, byFBOption);
		} else { /* RTS_needless, non PCF mode */
			struct vnt_rrv_time_ab *buf = pvRrvTime;

			buf->rrv_time = vnt_rxtx_rsvtime_le16(pDevice, PK_TYPE_11B, cbFrameSize, wCurrentRate, bNeedACK);
		}
	}
}