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
typedef  scalar_t__ u16 ;
struct pgpkt {int offset; int word_en; int /*<<< orphan*/  word_cnts; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ EFUSE_OOB_PROTECT_BYTES_88E ; 
 scalar_t__ EFUSE_REAL_CONTENT_LEN_88E ; 
 scalar_t__ EFUSE_REPEAT_THRESHOLD_ ; 
 int /*<<< orphan*/  Efuse_CalculateWordCnts (int) ; 
 int /*<<< orphan*/  efuse_OneByteRead (struct adapter*,scalar_t__,int*) ; 
 int /*<<< orphan*/  efuse_OneByteWrite (struct adapter*,scalar_t__,int) ; 
 int /*<<< orphan*/  hal_EfuseFixHeaderProcess (struct adapter*,int,struct pgpkt*,scalar_t__*) ; 

__attribute__((used)) static bool hal_EfusePgPacketWrite2ByteHeader(struct adapter *pAdapter, u8 efuseType, u16 *pAddr, struct pgpkt *pTargetPkt)
{
	bool ret = false;
	u16 efuse_addr = *pAddr;
	u16 efuse_max_available_len =
		EFUSE_REAL_CONTENT_LEN_88E - EFUSE_OOB_PROTECT_BYTES_88E;
	u8 pg_header = 0, tmp_header = 0, pg_header_temp = 0;
	u8 repeatcnt = 0;

	while (efuse_addr < efuse_max_available_len) {
		pg_header = ((pTargetPkt->offset & 0x07) << 5) | 0x0F;
		efuse_OneByteWrite(pAdapter, efuse_addr, pg_header);
		efuse_OneByteRead(pAdapter, efuse_addr, &tmp_header);

		while (tmp_header == 0xFF) {
			if (repeatcnt++ > EFUSE_REPEAT_THRESHOLD_)
				return false;

			efuse_OneByteWrite(pAdapter, efuse_addr, pg_header);
			efuse_OneByteRead(pAdapter, efuse_addr, &tmp_header);
		}

		/* to write ext_header */
		if (tmp_header == pg_header) {
			efuse_addr++;
			pg_header_temp = pg_header;
			pg_header = ((pTargetPkt->offset & 0x78) << 1) | pTargetPkt->word_en;

			efuse_OneByteWrite(pAdapter, efuse_addr, pg_header);
			efuse_OneByteRead(pAdapter, efuse_addr, &tmp_header);

			while (tmp_header == 0xFF) {
				if (repeatcnt++ > EFUSE_REPEAT_THRESHOLD_)
					return false;

				efuse_OneByteWrite(pAdapter, efuse_addr, pg_header);
				efuse_OneByteRead(pAdapter, efuse_addr, &tmp_header);
			}

			if ((tmp_header & 0x0F) == 0x0F) {	/* word_en PG fail */
				if (repeatcnt++ > EFUSE_REPEAT_THRESHOLD_)
					return false;

				efuse_addr++;
				continue;
			} else if (pg_header != tmp_header) {	/* offset PG fail */
				struct pgpkt	fixPkt;

				fixPkt.offset = ((pg_header_temp & 0xE0) >> 5) | ((tmp_header & 0xF0) >> 1);
				fixPkt.word_en = tmp_header & 0x0F;
				fixPkt.word_cnts = Efuse_CalculateWordCnts(fixPkt.word_en);
				if (!hal_EfuseFixHeaderProcess(pAdapter, efuseType, &fixPkt, &efuse_addr))
					return false;
			} else {
				ret = true;
				break;
			}
		} else if ((tmp_header & 0x1F) == 0x0F) {		/* wrong extended header */
			efuse_addr += 2;
			continue;
		}
	}

	*pAddr = efuse_addr;
	return ret;
}