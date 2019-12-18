#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_3__ {scalar_t__ btdmAntNum; scalar_t__ pgAntNum; } ;
struct TYPE_4__ {TYPE_1__ boardInfo; } ;

/* Variables and functions */
 scalar_t__ BT_COEX_ANT_TYPE_ANTDIV ; 
 scalar_t__ BT_COEX_ANT_TYPE_DETECTED ; 
 scalar_t__ BT_COEX_ANT_TYPE_PG ; 
 TYPE_2__ GLBtCoexist ; 

void EXhalbtcoutsrc_SetAntNum(u8 type, u8 antNum)
{
	if (BT_COEX_ANT_TYPE_PG == type) {
		GLBtCoexist.boardInfo.pgAntNum = antNum;
		GLBtCoexist.boardInfo.btdmAntNum = antNum;
	} else if (BT_COEX_ANT_TYPE_ANTDIV == type) {
		GLBtCoexist.boardInfo.btdmAntNum = antNum;
		/* GLBtCoexist.boardInfo.btdmAntPos = BTC_ANTENNA_AT_MAIN_PORT; */
	} else if (BT_COEX_ANT_TYPE_DETECTED == type) {
		GLBtCoexist.boardInfo.btdmAntNum = antNum;
		/* GLBtCoexist.boardInfo.btdmAntPos = BTC_ANTENNA_AT_MAIN_PORT; */
	}
}