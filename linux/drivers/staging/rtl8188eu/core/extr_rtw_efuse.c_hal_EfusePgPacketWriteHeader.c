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
struct pgpkt {scalar_t__ offset; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ EFUSE_MAX_SECTION_BASE ; 
 int hal_EfusePgPacketWrite1ByteHeader (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pgpkt*) ; 
 int hal_EfusePgPacketWrite2ByteHeader (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pgpkt*) ; 

__attribute__((used)) static bool
hal_EfusePgPacketWriteHeader(
				struct adapter *pAdapter,
				u8 efuseType,
				u16				*pAddr,
				struct pgpkt *pTargetPkt)
{
	bool ret = false;

	if (pTargetPkt->offset >= EFUSE_MAX_SECTION_BASE)
		ret = hal_EfusePgPacketWrite2ByteHeader(pAdapter, efuseType, pAddr, pTargetPkt);
	else
		ret = hal_EfusePgPacketWrite1ByteHeader(pAdapter, efuseType, pAddr, pTargetPkt);

	return ret;
}