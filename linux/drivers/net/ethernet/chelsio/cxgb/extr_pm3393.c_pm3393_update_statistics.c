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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct cmac_statistics {int dummy; } ;
struct cmac {struct cmac_statistics const stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  RMON_UPDATE (struct cmac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RxBroadcastFramesOK ; 
 int /*<<< orphan*/  RxBroadcastFramesReceivedOK ; 
 int /*<<< orphan*/  RxFCSErrors ; 
 int /*<<< orphan*/  RxFragments ; 
 int /*<<< orphan*/  RxFrameCheckSequenceErrors ; 
 int /*<<< orphan*/  RxFrameTooLongErrors ; 
 int /*<<< orphan*/  RxFramesLostDueToInternalMACErrors ; 
 int /*<<< orphan*/  RxFramesTooLongErrors ; 
 int /*<<< orphan*/  RxInRangeLengthErrors ; 
 int /*<<< orphan*/  RxInternalMACRcvError ; 
 int /*<<< orphan*/  RxJabberErrors ; 
 int /*<<< orphan*/  RxJabbers ; 
 int /*<<< orphan*/  RxJumboFramesOK ; 
 int /*<<< orphan*/  RxJumboFramesReceivedOK ; 
 int /*<<< orphan*/  RxJumboOctetsOK ; 
 int /*<<< orphan*/  RxJumboOctetsReceivedOK ; 
 int /*<<< orphan*/  RxMulticastFramesOK ; 
 int /*<<< orphan*/  RxMulticastFramesReceivedOK ; 
 int /*<<< orphan*/  RxOctetsOK ; 
 int /*<<< orphan*/  RxOctetsReceivedOK ; 
 int /*<<< orphan*/  RxPAUSEMACCtrlFramesReceived ; 
 int /*<<< orphan*/  RxPauseFrames ; 
 int /*<<< orphan*/  RxRuntErrors ; 
 int /*<<< orphan*/  RxSymbolErrors ; 
 int /*<<< orphan*/  RxUndersizedFrames ; 
 int /*<<< orphan*/  RxUnicastFramesOK ; 
 int /*<<< orphan*/  RxUnicastFramesReceivedOK ; 
 int /*<<< orphan*/  SUNI1x10GEXP_BITMSK_MSTAT_SNAP ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_MSTAT_CONTROL ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_MSTAT_COUNTER_ROLLOVER_0 ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_MSTAT_COUNTER_ROLLOVER_1 ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_MSTAT_COUNTER_ROLLOVER_2 ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_MSTAT_COUNTER_ROLLOVER_3 ; 
 int /*<<< orphan*/  TxBroadcastFramesOK ; 
 int /*<<< orphan*/  TxBroadcastFramesTransmittedOK ; 
 int /*<<< orphan*/  TxFCSErrors ; 
 int /*<<< orphan*/  TxFramesLostDueToInternalMACTransmissionError ; 
 int /*<<< orphan*/  TxInternalMACXmitError ; 
 int /*<<< orphan*/  TxJumboFramesOK ; 
 int /*<<< orphan*/  TxJumboFramesReceivedOK ; 
 int /*<<< orphan*/  TxJumboOctetsOK ; 
 int /*<<< orphan*/  TxJumboOctetsReceivedOK ; 
 int /*<<< orphan*/  TxMulticastFramesOK ; 
 int /*<<< orphan*/  TxMulticastFramesTransmittedOK ; 
 int /*<<< orphan*/  TxOctetsOK ; 
 int /*<<< orphan*/  TxOctetsTransmittedOK ; 
 int /*<<< orphan*/  TxPAUSEMACCtrlFramesTransmitted ; 
 int /*<<< orphan*/  TxPauseFrames ; 
 int /*<<< orphan*/  TxTransmitSystemError ; 
 int /*<<< orphan*/  TxUnicastFramesOK ; 
 int /*<<< orphan*/  TxUnicastFramesTransmittedOK ; 
 int /*<<< orphan*/  pmread (struct cmac*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pmwrite (struct cmac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct cmac_statistics *pm3393_update_statistics(struct cmac *mac,
							      int flag)
{
	u64	ro;
	u32	val0, val1, val2, val3;

	/* Snap the counters */
	pmwrite(mac, SUNI1x10GEXP_REG_MSTAT_CONTROL,
		SUNI1x10GEXP_BITMSK_MSTAT_SNAP);

	/* Counter rollover, clear on read */
	pmread(mac, SUNI1x10GEXP_REG_MSTAT_COUNTER_ROLLOVER_0, &val0);
	pmread(mac, SUNI1x10GEXP_REG_MSTAT_COUNTER_ROLLOVER_1, &val1);
	pmread(mac, SUNI1x10GEXP_REG_MSTAT_COUNTER_ROLLOVER_2, &val2);
	pmread(mac, SUNI1x10GEXP_REG_MSTAT_COUNTER_ROLLOVER_3, &val3);
	ro = ((u64)val0 & 0xffff) | (((u64)val1 & 0xffff) << 16) |
		(((u64)val2 & 0xffff) << 32) | (((u64)val3 & 0xffff) << 48);

	/* Rx stats */
	RMON_UPDATE(mac, RxOctetsReceivedOK, RxOctetsOK);
	RMON_UPDATE(mac, RxUnicastFramesReceivedOK, RxUnicastFramesOK);
	RMON_UPDATE(mac, RxMulticastFramesReceivedOK, RxMulticastFramesOK);
	RMON_UPDATE(mac, RxBroadcastFramesReceivedOK, RxBroadcastFramesOK);
	RMON_UPDATE(mac, RxPAUSEMACCtrlFramesReceived, RxPauseFrames);
	RMON_UPDATE(mac, RxFrameCheckSequenceErrors, RxFCSErrors);
	RMON_UPDATE(mac, RxFramesLostDueToInternalMACErrors,
				RxInternalMACRcvError);
	RMON_UPDATE(mac, RxSymbolErrors, RxSymbolErrors);
	RMON_UPDATE(mac, RxInRangeLengthErrors, RxInRangeLengthErrors);
	RMON_UPDATE(mac, RxFramesTooLongErrors , RxFrameTooLongErrors);
	RMON_UPDATE(mac, RxJabbers, RxJabberErrors);
	RMON_UPDATE(mac, RxFragments, RxRuntErrors);
	RMON_UPDATE(mac, RxUndersizedFrames, RxRuntErrors);
	RMON_UPDATE(mac, RxJumboFramesReceivedOK, RxJumboFramesOK);
	RMON_UPDATE(mac, RxJumboOctetsReceivedOK, RxJumboOctetsOK);

	/* Tx stats */
	RMON_UPDATE(mac, TxOctetsTransmittedOK, TxOctetsOK);
	RMON_UPDATE(mac, TxFramesLostDueToInternalMACTransmissionError,
				TxInternalMACXmitError);
	RMON_UPDATE(mac, TxTransmitSystemError, TxFCSErrors);
	RMON_UPDATE(mac, TxUnicastFramesTransmittedOK, TxUnicastFramesOK);
	RMON_UPDATE(mac, TxMulticastFramesTransmittedOK, TxMulticastFramesOK);
	RMON_UPDATE(mac, TxBroadcastFramesTransmittedOK, TxBroadcastFramesOK);
	RMON_UPDATE(mac, TxPAUSEMACCtrlFramesTransmitted, TxPauseFrames);
	RMON_UPDATE(mac, TxJumboFramesReceivedOK, TxJumboFramesOK);
	RMON_UPDATE(mac, TxJumboOctetsReceivedOK, TxJumboOctetsOK);

	return &mac->stats;
}