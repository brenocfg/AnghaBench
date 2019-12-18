#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_9__ {int btdmAntNum; } ;
struct TYPE_8__ {int /*<<< orphan*/  cntSpecialPacketNotify; } ;
struct TYPE_10__ {TYPE_2__ boardInfo; scalar_t__ bManualControl; TYPE_1__ statistics; } ;
typedef  TYPE_3__* PBTC_COEXIST ;

/* Variables and functions */
 scalar_t__ BTC_PACKET_ARP ; 
 scalar_t__ BTC_PACKET_DHCP ; 
 scalar_t__ BTC_PACKET_EAPOL ; 
 int /*<<< orphan*/  EXhalbtc8723b1ant_SpecialPacketNotify (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  EXhalbtc8723b2ant_SpecialPacketNotify (TYPE_3__*,scalar_t__) ; 
 scalar_t__ PACKET_ARP ; 
 scalar_t__ PACKET_DHCP ; 
 scalar_t__ PACKET_EAPOL ; 
 int /*<<< orphan*/  halbtcoutsrc_IsBtCoexistAvailable (TYPE_3__*) ; 

void EXhalbtcoutsrc_SpecialPacketNotify(PBTC_COEXIST pBtCoexist, u8 pktType)
{
	u8 packetType;

	if (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		return;
	pBtCoexist->statistics.cntSpecialPacketNotify++;
	if (pBtCoexist->bManualControl)
		return;

	if (PACKET_DHCP == pktType) {
		packetType = BTC_PACKET_DHCP;
	} else if (PACKET_EAPOL == pktType) {
		packetType = BTC_PACKET_EAPOL;
	} else if (PACKET_ARP == pktType) {
		packetType = BTC_PACKET_ARP;
	} else {
		return;
	}

	/*  All notify is called in cmd thread, don't need to leave low power again */
/* 	halbtcoutsrc_LeaveLowPower(pBtCoexist); */

	if (pBtCoexist->boardInfo.btdmAntNum == 2)
		EXhalbtc8723b2ant_SpecialPacketNotify(pBtCoexist, packetType);
	else if (pBtCoexist->boardInfo.btdmAntNum == 1)
		EXhalbtc8723b1ant_SpecialPacketNotify(pBtCoexist, packetType);

/* 	halbtcoutsrc_NormalLowPower(pBtCoexist); */
}