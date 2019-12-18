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
struct pgpkt {int /*<<< orphan*/  data; int /*<<< orphan*/  offset; int /*<<< orphan*/  word_en; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ Efuse_PgPacketWrite (struct adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int Efuse_WordEnableDataWrite (struct adapter*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hal_EfusePgPacketWriteData(struct adapter *pAdapter, u8 efuseType, u16 *pAddr, struct pgpkt *pTargetPkt)
{
	u16	efuse_addr = *pAddr;
	u8 badworden = 0;
	u32	PgWriteSuccess = 0;

	badworden = 0x0f;
	badworden = Efuse_WordEnableDataWrite(pAdapter, efuse_addr + 1, pTargetPkt->word_en, pTargetPkt->data);
	if (badworden == 0x0F) {
		/*  write ok */
		return true;
	}
	/* reorganize other pg packet */
	PgWriteSuccess = Efuse_PgPacketWrite(pAdapter, pTargetPkt->offset, badworden, pTargetPkt->data);
	if (!PgWriteSuccess)
		return false;
	else
		return true;
}