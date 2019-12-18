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
typedef  scalar_t__ u16 ;
struct pgpkt {int word_cnts; int /*<<< orphan*/  offset; int /*<<< orphan*/  word_en; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ Efuse_GetCurrentSize (struct adapter*) ; 
 scalar_t__ Efuse_PgPacketRead (struct adapter*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ Efuse_PgPacketWrite (struct adapter*,int /*<<< orphan*/ ,int,int*) ; 
 int Efuse_WordEnableDataWrite (struct adapter*,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static bool hal_EfuseFixHeaderProcess(struct adapter *pAdapter, u8 efuseType, struct pgpkt *pFixPkt, u16 *pAddr)
{
	u8 originaldata[8], badworden = 0;
	u16	efuse_addr = *pAddr;
	u32	PgWriteSuccess = 0;

	memset(originaldata, 0xff, 8);

	if (Efuse_PgPacketRead(pAdapter, pFixPkt->offset, originaldata)) {
		/* check if data exist */
		badworden = Efuse_WordEnableDataWrite(pAdapter, efuse_addr + 1, pFixPkt->word_en, originaldata);

		if (badworden != 0xf) {	/*  write fail */
			PgWriteSuccess = Efuse_PgPacketWrite(pAdapter, pFixPkt->offset, badworden, originaldata);

			if (!PgWriteSuccess)
				return false;
			else
				efuse_addr = Efuse_GetCurrentSize(pAdapter);
		} else {
			efuse_addr = efuse_addr + (pFixPkt->word_cnts * 2) + 1;
		}
	} else {
		efuse_addr = efuse_addr + (pFixPkt->word_cnts * 2) + 1;
	}
	*pAddr = efuse_addr;
	return true;
}