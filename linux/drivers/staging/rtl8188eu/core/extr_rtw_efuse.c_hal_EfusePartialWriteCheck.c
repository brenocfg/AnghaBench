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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct pgpkt {int offset; int word_en; int word_cnts; int /*<<< orphan*/  data; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALL_WORDS_DISABLED (int) ; 
 int EFUSE_OOB_PROTECT_BYTES_88E ; 
 int EFUSE_REAL_CONTENT_LEN ; 
 int EFUSE_REAL_CONTENT_LEN_88E ; 
 scalar_t__ EXT_HEADER (int) ; 
 void* Efuse_CalculateWordCnts (int) ; 
 scalar_t__ Efuse_PgPacketWrite (struct adapter*,int,int,int /*<<< orphan*/ ) ; 
 int Efuse_WordEnableDataWrite (struct adapter*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HW_VAR_EFUSE_BYTES ; 
 scalar_t__ efuse_OneByteRead (struct adapter*,int,int*) ; 
 int /*<<< orphan*/  hal_EfuseCheckIfDatafollowed (struct adapter*,int,int) ; 
 int /*<<< orphan*/  rtw_hal_get_hwreg (struct adapter*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ wordEnMatched (struct pgpkt*,struct pgpkt*,int*) ; 

__attribute__((used)) static bool hal_EfusePartialWriteCheck(struct adapter *pAdapter, u8 efuseType, u16 *pAddr, struct pgpkt *pTargetPkt)
{
	bool ret = false;
	u8 i, efuse_data = 0, cur_header = 0;
	u8 matched_wden = 0, badworden = 0;
	u16 startAddr = 0;
	u16 efuse_max_available_len =
		EFUSE_REAL_CONTENT_LEN_88E - EFUSE_OOB_PROTECT_BYTES_88E;
	struct pgpkt curPkt;

	rtw_hal_get_hwreg(pAdapter, HW_VAR_EFUSE_BYTES, (u8 *)&startAddr);
	startAddr %= EFUSE_REAL_CONTENT_LEN;

	while (1) {
		if (startAddr >= efuse_max_available_len) {
			ret = false;
			break;
		}

		if (efuse_OneByteRead(pAdapter, startAddr, &efuse_data) && (efuse_data != 0xFF)) {
			if (EXT_HEADER(efuse_data)) {
				cur_header = efuse_data;
				startAddr++;
				efuse_OneByteRead(pAdapter, startAddr, &efuse_data);
				if (ALL_WORDS_DISABLED(efuse_data)) {
					ret = false;
					break;
				} else {
					curPkt.offset = ((cur_header & 0xE0) >> 5) | ((efuse_data & 0xF0) >> 1);
					curPkt.word_en = efuse_data & 0x0F;
				}
			} else {
				cur_header  =  efuse_data;
				curPkt.offset = (cur_header >> 4) & 0x0F;
				curPkt.word_en = cur_header & 0x0F;
			}

			curPkt.word_cnts = Efuse_CalculateWordCnts(curPkt.word_en);
			/*  if same header is found but no data followed */
			/*  write some part of data followed by the header. */
			if ((curPkt.offset == pTargetPkt->offset) &&
			    (!hal_EfuseCheckIfDatafollowed(pAdapter, curPkt.word_cnts, startAddr + 1)) &&
			    wordEnMatched(pTargetPkt, &curPkt, &matched_wden)) {
				/*  Here to write partial data */
				badworden = Efuse_WordEnableDataWrite(pAdapter, startAddr + 1, matched_wden, pTargetPkt->data);
				if (badworden != 0x0F) {
					u32	PgWriteSuccess = 0;
					/*  if write fail on some words, write these bad words again */

					PgWriteSuccess = Efuse_PgPacketWrite(pAdapter, pTargetPkt->offset, badworden, pTargetPkt->data);

					if (!PgWriteSuccess) {
						ret = false;	/*  write fail, return */
						break;
					}
				}
				/*  partial write ok, update the target packet for later use */
				for (i = 0; i < 4; i++) {
					if ((matched_wden & (0x1 << i)) == 0)	/*  this word has been written */
						pTargetPkt->word_en |= (0x1 << i);	/*  disable the word */
				}
				pTargetPkt->word_cnts = Efuse_CalculateWordCnts(pTargetPkt->word_en);
			}
			/*  read from next header */
			startAddr = startAddr + (curPkt.word_cnts * 2) + 1;
		} else {
			/*  not used header, 0xff */
			*pAddr = startAddr;
			ret = true;
			break;
		}
	}
	return ret;
}