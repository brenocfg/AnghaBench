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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ath_tx_info {int qcu; int link; int* buf_addr; int* buf_len; int keytype; int pkt_len; int flags; int* txpower; scalar_t__ keyix; int type; int aggr; int aggr_len; int ndelim; int rtscts_rate; int /*<<< orphan*/  rates; scalar_t__ is_last; scalar_t__ is_first; scalar_t__ dur_update; } ;
struct ath_hw {int dummy; } ;
struct ar9003_txc {scalar_t__ ctl22; scalar_t__ ctl21; scalar_t__ ctl20; scalar_t__ ctl19; scalar_t__ ctl18; scalar_t__ ctl16; scalar_t__ ctl15; scalar_t__ ctl17; scalar_t__ ctl12; scalar_t__ ctl11; scalar_t__ ctl23; scalar_t__ ctl14; scalar_t__ ctl13; scalar_t__ ctl10; scalar_t__ ctl9; scalar_t__ ctl7; scalar_t__ ctl5; scalar_t__ ctl3; scalar_t__ data3; scalar_t__ data2; scalar_t__ data1; scalar_t__ data0; scalar_t__ link; scalar_t__ info; } ;

/* Variables and functions */
#define  AGGR_BUF_FIRST 131 
#define  AGGR_BUF_LAST 130 
#define  AGGR_BUF_MIDDLE 129 
#define  AGGR_BUF_NONE 128 
 int /*<<< orphan*/  AR_AggrLen ; 
 int AR_BufLen ; 
 int AR_BufLen_S ; 
 int /*<<< orphan*/  AR_BurstDur ; 
 int AR_CTSEnable ; 
 int AR_ClrDestMask ; 
 int AR_CtrlStat_S ; 
 int AR_DescId_S ; 
 int /*<<< orphan*/  AR_DestIdx ; 
 int AR_DestIdxValid ; 
 int AR_DurUpdateEna ; 
 int /*<<< orphan*/  AR_EncrType ; 
 int AR_ExtAndCtl ; 
 int AR_ExtOnly ; 
 int AR_FrameLen ; 
 int /*<<< orphan*/  AR_FrameType ; 
 int AR_IsAggr ; 
 int AR_LDPC ; 
 int AR_LowRxChain ; 
 int AR_MoreAggr ; 
 int AR_NoAck ; 
 int AR_Not_Sounding ; 
 int /*<<< orphan*/  AR_PAPRDChainMask ; 
 int /*<<< orphan*/  AR_PadDelim ; 
 int /*<<< orphan*/  AR_RTSCTSRate ; 
 int AR_RTSEnable ; 
 scalar_t__ AR_SREV_9462 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 int AR_TxMore ; 
 int AR_TxQcuNum_S ; 
 int AR_TxRxDesc_S ; 
 int AR_VEOL ; 
 int AR_VirtMoreFrag ; 
 int /*<<< orphan*/  AR_XmitPower0 ; 
 int /*<<< orphan*/  AR_XmitPower1 ; 
 int /*<<< orphan*/  AR_XmitPower2 ; 
 int /*<<< orphan*/  AR_XmitPower3 ; 
 int ATH9K_TXDESC_CLRDMASK ; 
 int ATH9K_TXDESC_CTSENA ; 
 int ATH9K_TXDESC_EXT_AND_CTL ; 
 int ATH9K_TXDESC_EXT_ONLY ; 
 int ATH9K_TXDESC_LDPC ; 
 int ATH9K_TXDESC_LOWRXCHAIN ; 
 int ATH9K_TXDESC_NOACK ; 
 int ATH9K_TXDESC_PAPRD ; 
 int ATH9K_TXDESC_PAPRD_S ; 
 int ATH9K_TXDESC_RTSENA ; 
 int ATH9K_TXDESC_VEOL ; 
 int ATH9K_TXDESC_VMF ; 
 scalar_t__ ATH9K_TXKEYIX_INVALID ; 
 int ATHEROS_VENDOR_ID ; 
 int SM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (scalar_t__,int) ; 
 int set11nPktDurRTSCTS (int /*<<< orphan*/ ,int) ; 
 int set11nRate (int /*<<< orphan*/ ,int) ; 
 int set11nRateFlags (int /*<<< orphan*/ ,int) ; 
 int set11nTries (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ar9003_set_txdesc(struct ath_hw *ah, void *ds, struct ath_tx_info *i)
{
	struct ar9003_txc *ads = ds;
	int checksum = 0;
	u32 val, ctl12, ctl17;
	u8 desc_len;

	desc_len = ((AR_SREV_9462(ah) || AR_SREV_9565(ah)) ? 0x18 : 0x17);

	val = (ATHEROS_VENDOR_ID << AR_DescId_S) |
	      (1 << AR_TxRxDesc_S) |
	      (1 << AR_CtrlStat_S) |
	      (i->qcu << AR_TxQcuNum_S) | desc_len;

	checksum += val;
	WRITE_ONCE(ads->info, val);

	checksum += i->link;
	WRITE_ONCE(ads->link, i->link);

	checksum += i->buf_addr[0];
	WRITE_ONCE(ads->data0, i->buf_addr[0]);
	checksum += i->buf_addr[1];
	WRITE_ONCE(ads->data1, i->buf_addr[1]);
	checksum += i->buf_addr[2];
	WRITE_ONCE(ads->data2, i->buf_addr[2]);
	checksum += i->buf_addr[3];
	WRITE_ONCE(ads->data3, i->buf_addr[3]);

	checksum += (val = (i->buf_len[0] << AR_BufLen_S) & AR_BufLen);
	WRITE_ONCE(ads->ctl3, val);
	checksum += (val = (i->buf_len[1] << AR_BufLen_S) & AR_BufLen);
	WRITE_ONCE(ads->ctl5, val);
	checksum += (val = (i->buf_len[2] << AR_BufLen_S) & AR_BufLen);
	WRITE_ONCE(ads->ctl7, val);
	checksum += (val = (i->buf_len[3] << AR_BufLen_S) & AR_BufLen);
	WRITE_ONCE(ads->ctl9, val);

	checksum = (u16) (((checksum & 0xffff) + (checksum >> 16)) & 0xffff);
	WRITE_ONCE(ads->ctl10, checksum);

	if (i->is_first || i->is_last) {
		WRITE_ONCE(ads->ctl13, set11nTries(i->rates, 0)
			| set11nTries(i->rates, 1)
			| set11nTries(i->rates, 2)
			| set11nTries(i->rates, 3)
			| (i->dur_update ? AR_DurUpdateEna : 0)
			| SM(0, AR_BurstDur));

		WRITE_ONCE(ads->ctl14, set11nRate(i->rates, 0)
			| set11nRate(i->rates, 1)
			| set11nRate(i->rates, 2)
			| set11nRate(i->rates, 3));
	} else {
		WRITE_ONCE(ads->ctl13, 0);
		WRITE_ONCE(ads->ctl14, 0);
	}

	ads->ctl20 = 0;
	ads->ctl21 = 0;
	ads->ctl22 = 0;
	ads->ctl23 = 0;

	ctl17 = SM(i->keytype, AR_EncrType);
	if (!i->is_first) {
		WRITE_ONCE(ads->ctl11, 0);
		WRITE_ONCE(ads->ctl12, i->is_last ? 0 : AR_TxMore);
		WRITE_ONCE(ads->ctl15, 0);
		WRITE_ONCE(ads->ctl16, 0);
		WRITE_ONCE(ads->ctl17, ctl17);
		WRITE_ONCE(ads->ctl18, 0);
		WRITE_ONCE(ads->ctl19, 0);
		return;
	}

	WRITE_ONCE(ads->ctl11, (i->pkt_len & AR_FrameLen)
		| (i->flags & ATH9K_TXDESC_VMF ? AR_VirtMoreFrag : 0)
		| SM(i->txpower[0], AR_XmitPower0)
		| (i->flags & ATH9K_TXDESC_VEOL ? AR_VEOL : 0)
		| (i->keyix != ATH9K_TXKEYIX_INVALID ? AR_DestIdxValid : 0)
		| (i->flags & ATH9K_TXDESC_LOWRXCHAIN ? AR_LowRxChain : 0)
		| (i->flags & ATH9K_TXDESC_CLRDMASK ? AR_ClrDestMask : 0)
		| (i->flags & ATH9K_TXDESC_RTSENA ? AR_RTSEnable :
		   (i->flags & ATH9K_TXDESC_CTSENA ? AR_CTSEnable : 0)));

	ctl12 = (i->keyix != ATH9K_TXKEYIX_INVALID ?
		 SM(i->keyix, AR_DestIdx) : 0)
		| SM(i->type, AR_FrameType)
		| (i->flags & ATH9K_TXDESC_NOACK ? AR_NoAck : 0)
		| (i->flags & ATH9K_TXDESC_EXT_ONLY ? AR_ExtOnly : 0)
		| (i->flags & ATH9K_TXDESC_EXT_AND_CTL ? AR_ExtAndCtl : 0);

	ctl17 |= (i->flags & ATH9K_TXDESC_LDPC ? AR_LDPC : 0);
	switch (i->aggr) {
	case AGGR_BUF_FIRST:
		ctl17 |= SM(i->aggr_len, AR_AggrLen);
		/* fall through */
	case AGGR_BUF_MIDDLE:
		ctl12 |= AR_IsAggr | AR_MoreAggr;
		ctl17 |= SM(i->ndelim, AR_PadDelim);
		break;
	case AGGR_BUF_LAST:
		ctl12 |= AR_IsAggr;
		break;
	case AGGR_BUF_NONE:
		break;
	}

	val = (i->flags & ATH9K_TXDESC_PAPRD) >> ATH9K_TXDESC_PAPRD_S;
	ctl12 |= SM(val, AR_PAPRDChainMask);

	WRITE_ONCE(ads->ctl12, ctl12);
	WRITE_ONCE(ads->ctl17, ctl17);

	WRITE_ONCE(ads->ctl15, set11nPktDurRTSCTS(i->rates, 0)
		| set11nPktDurRTSCTS(i->rates, 1));

	WRITE_ONCE(ads->ctl16, set11nPktDurRTSCTS(i->rates, 2)
		| set11nPktDurRTSCTS(i->rates, 3));

	WRITE_ONCE(ads->ctl18, set11nRateFlags(i->rates, 0)
		| set11nRateFlags(i->rates, 1)
		| set11nRateFlags(i->rates, 2)
		| set11nRateFlags(i->rates, 3)
		| SM(i->rtscts_rate, AR_RTSCTSRate));

	WRITE_ONCE(ads->ctl19, AR_Not_Sounding);

	WRITE_ONCE(ads->ctl20, SM(i->txpower[1], AR_XmitPower1));
	WRITE_ONCE(ads->ctl21, SM(i->txpower[2], AR_XmitPower2));
	WRITE_ONCE(ads->ctl22, SM(i->txpower[3], AR_XmitPower3));
}