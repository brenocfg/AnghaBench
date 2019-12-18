#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_9__ {int /*<<< orphan*/  btdmAntPos; } ;
struct TYPE_8__ {int bBtCtrlAggBufSize; int aggBufSize; int bIncreaseScanDevNum; } ;
struct TYPE_7__ {int bProfileNotified; } ;
struct TYPE_10__ {int /*<<< orphan*/  cntBind; } ;
struct TYPE_11__ {int bBinded; TYPE_3__ boardInfo; TYPE_2__ btInfo; TYPE_1__ stackInfo; void* Adapter; TYPE_4__ statistics; } ;
typedef  TYPE_5__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANTENNA_AT_MAIN_PORT ; 
 TYPE_5__ GLBtCoexist ; 

__attribute__((used)) static u8 EXhalbtcoutsrc_BindBtCoexWithAdapter(void *padapter)
{
	PBTC_COEXIST		pBtCoexist = &GLBtCoexist;

	if (pBtCoexist->bBinded)
		return false;
	else
		pBtCoexist->bBinded = true;

	pBtCoexist->statistics.cntBind++;

	pBtCoexist->Adapter = padapter;

	pBtCoexist->stackInfo.bProfileNotified = false;

	pBtCoexist->btInfo.bBtCtrlAggBufSize = false;
	pBtCoexist->btInfo.aggBufSize = 5;

	pBtCoexist->btInfo.bIncreaseScanDevNum = false;

	/*  set default antenna position to main  port */
	pBtCoexist->boardInfo.btdmAntPos = BTC_ANTENNA_AT_MAIN_PORT;

	return true;
}