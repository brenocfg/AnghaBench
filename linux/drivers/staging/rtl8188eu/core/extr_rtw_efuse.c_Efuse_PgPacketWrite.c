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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pgpkt {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ EFUSE_MAP_LEN_88E ; 
 int /*<<< orphan*/  EFUSE_WIFI ; 
 scalar_t__ Efuse_GetCurrentSize (struct adapter*) ; 
 int /*<<< orphan*/  hal_EfuseConstructPGPkt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pgpkt*) ; 
 int /*<<< orphan*/  hal_EfusePartialWriteCheck (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pgpkt*) ; 
 int /*<<< orphan*/  hal_EfusePgPacketWriteData (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pgpkt*) ; 
 int /*<<< orphan*/  hal_EfusePgPacketWriteHeader (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pgpkt*) ; 

bool Efuse_PgPacketWrite(struct adapter *pAdapter, u8 offset, u8 word_en, u8 *pData)
{
	struct pgpkt	targetPkt;
	u16			startAddr = 0;
	u8 efuseType = EFUSE_WIFI;

	if (Efuse_GetCurrentSize(pAdapter) >= EFUSE_MAP_LEN_88E)
		return false;

	hal_EfuseConstructPGPkt(offset, word_en, pData, &targetPkt);

	if (!hal_EfusePartialWriteCheck(pAdapter, efuseType, &startAddr, &targetPkt))
		return false;

	if (!hal_EfusePgPacketWriteHeader(pAdapter, efuseType, &startAddr, &targetPkt))
		return false;

	if (!hal_EfusePgPacketWriteData(pAdapter, efuseType, &startAddr, &targetPkt))
		return false;

	return true;
}