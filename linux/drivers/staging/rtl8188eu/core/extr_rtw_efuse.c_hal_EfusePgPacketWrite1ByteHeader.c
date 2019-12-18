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
typedef  int /*<<< orphan*/  u16 ;
struct pgpkt {int offset; int word_en; int /*<<< orphan*/  word_cnts; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ EFUSE_REPEAT_THRESHOLD_ ; 
 int /*<<< orphan*/  Efuse_CalculateWordCnts (int) ; 
 int /*<<< orphan*/  efuse_OneByteRead (struct adapter*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  efuse_OneByteWrite (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hal_EfuseFixHeaderProcess (struct adapter*,int,struct pgpkt*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool hal_EfusePgPacketWrite1ByteHeader(struct adapter *pAdapter, u8 efuseType, u16 *pAddr, struct pgpkt *pTargetPkt)
{
	bool ret = false;
	u8 pg_header = 0, tmp_header = 0;
	u16	efuse_addr = *pAddr;
	u8 repeatcnt = 0;

	pg_header = ((pTargetPkt->offset << 4) & 0xf0) | pTargetPkt->word_en;

	efuse_OneByteWrite(pAdapter, efuse_addr, pg_header);
	efuse_OneByteRead(pAdapter, efuse_addr, &tmp_header);

	while (tmp_header == 0xFF) {
		if (repeatcnt++ > EFUSE_REPEAT_THRESHOLD_)
			return false;
		efuse_OneByteWrite(pAdapter, efuse_addr, pg_header);
		efuse_OneByteRead(pAdapter, efuse_addr, &tmp_header);
	}

	if (pg_header == tmp_header) {
		ret = true;
	} else {
		struct pgpkt	fixPkt;

		fixPkt.offset = (tmp_header >> 4) & 0x0F;
		fixPkt.word_en = tmp_header & 0x0F;
		fixPkt.word_cnts = Efuse_CalculateWordCnts(fixPkt.word_en);
		if (!hal_EfuseFixHeaderProcess(pAdapter, efuseType, &fixPkt, &efuse_addr))
			return false;
	}

	*pAddr = efuse_addr;
	return ret;
}