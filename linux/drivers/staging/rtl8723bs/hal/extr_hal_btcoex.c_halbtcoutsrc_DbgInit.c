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
typedef  size_t u8 ;

/* Variables and functions */
 size_t BTC_MSG_ALGORITHM ; 
 size_t BTC_MSG_INTERFACE ; 
 size_t BTC_MSG_MAX ; 
 scalar_t__* GLBtcDbgType ; 

__attribute__((used)) static void halbtcoutsrc_DbgInit(void)
{
	u8 i;

	for (i = 0; i < BTC_MSG_MAX; i++)
		GLBtcDbgType[i] = 0;

	GLBtcDbgType[BTC_MSG_INTERFACE]			=	\
/* 			INTF_INIT								| */
/* 			INTF_NOTIFY							| */
			0;

	GLBtcDbgType[BTC_MSG_ALGORITHM]			=	\
/* 			ALGO_BT_RSSI_STATE					| */
/* 			ALGO_WIFI_RSSI_STATE					| */
/* 			ALGO_BT_MONITOR						| */
/* 			ALGO_TRACE							| */
/* 			ALGO_TRACE_FW						| */
/* 			ALGO_TRACE_FW_DETAIL				| */
/* 			ALGO_TRACE_FW_EXEC					| */
/* 			ALGO_TRACE_SW						| */
/* 			ALGO_TRACE_SW_DETAIL				| */
/* 			ALGO_TRACE_SW_EXEC					| */
			0;
}