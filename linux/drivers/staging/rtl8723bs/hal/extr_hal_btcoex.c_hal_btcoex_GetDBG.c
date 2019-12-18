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
typedef  scalar_t__ u32 ;
struct adapter {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int ALGO_BT_MONITOR ; 
 int ALGO_BT_RSSI_STATE ; 
 int ALGO_TRACE ; 
 int ALGO_TRACE_FW ; 
 int ALGO_TRACE_FW_DETAIL ; 
 int ALGO_TRACE_FW_EXEC ; 
 int ALGO_TRACE_SW ; 
 int ALGO_TRACE_SW_DETAIL ; 
 int ALGO_TRACE_SW_EXEC ; 
 int ALGO_WIFI_RSSI_STATE ; 
 size_t BTC_MSG_ALGORITHM ; 
 size_t BTC_MSG_INTERFACE ; 
 int DBG ; 
 int* GLBtcDbgType ; 
 int INTF_INIT ; 
 int INTF_NOTIFY ; 
 scalar_t__ rtw_sprintf (int /*<<< orphan*/ *,scalar_t__,char*,...) ; 

u32 hal_btcoex_GetDBG(struct adapter *padapter, u8 *pStrBuf, u32 bufSize)
{
	s32 count;
	u8 *pstr;
	u32 leftSize;


	if (!pStrBuf || bufSize == 0)
		return 0;

	pstr = pStrBuf;
	leftSize = bufSize;
/* 	DBG_871X(FUNC_ADPT_FMT ": bufsize =%d\n", FUNC_ADPT_ARG(padapter), bufSize); */

	count = rtw_sprintf(pstr, leftSize, "#define DBG\t%d\n", DBG);
	if ((count < 0) || (count >= leftSize))
		goto exit;
	pstr += count;
	leftSize -= count;

	count = rtw_sprintf(pstr, leftSize, "BTCOEX Debug Setting:\n");
	if ((count < 0) || (count >= leftSize))
		goto exit;
	pstr += count;
	leftSize -= count;

	count = rtw_sprintf(pstr, leftSize,
		"INTERFACE / ALGORITHM: 0x%08X / 0x%08X\n\n",
		GLBtcDbgType[BTC_MSG_INTERFACE],
		GLBtcDbgType[BTC_MSG_ALGORITHM]);
	if ((count < 0) || (count >= leftSize))
		goto exit;
	pstr += count;
	leftSize -= count;

	count = rtw_sprintf(pstr, leftSize, "INTERFACE Debug Setting Definition:\n");
	if ((count < 0) || (count >= leftSize))
		goto exit;
	pstr += count;
	leftSize -= count;
	count = rtw_sprintf(pstr, leftSize, "\tbit[0]=%d for INTF_INIT\n",
		(GLBtcDbgType[BTC_MSG_INTERFACE]&INTF_INIT)?1:0);
	if ((count < 0) || (count >= leftSize))
		goto exit;
	pstr += count;
	leftSize -= count;
	count = rtw_sprintf(pstr, leftSize, "\tbit[2]=%d for INTF_NOTIFY\n\n",
		(GLBtcDbgType[BTC_MSG_INTERFACE]&INTF_NOTIFY)?1:0);
	if ((count < 0) || (count >= leftSize))
		goto exit;
	pstr += count;
	leftSize -= count;

	count = rtw_sprintf(pstr, leftSize, "ALGORITHM Debug Setting Definition:\n");
	if ((count < 0) || (count >= leftSize))
		goto exit;
	pstr += count;
	leftSize -= count;
	count = rtw_sprintf(pstr, leftSize, "\tbit[0]=%d for BT_RSSI_STATE\n",
		(GLBtcDbgType[BTC_MSG_ALGORITHM]&ALGO_BT_RSSI_STATE)?1:0);
	if ((count < 0) || (count >= leftSize))
		goto exit;
	pstr += count;
	leftSize -= count;
	count = rtw_sprintf(pstr, leftSize, "\tbit[1]=%d for WIFI_RSSI_STATE\n",
		(GLBtcDbgType[BTC_MSG_ALGORITHM]&ALGO_WIFI_RSSI_STATE)?1:0);
	if ((count < 0) || (count >= leftSize))
		goto exit;
	pstr += count;
	leftSize -= count;
	count = rtw_sprintf(pstr, leftSize, "\tbit[2]=%d for BT_MONITOR\n",
		(GLBtcDbgType[BTC_MSG_ALGORITHM]&ALGO_BT_MONITOR)?1:0);
	if ((count < 0) || (count >= leftSize))
		goto exit;
	pstr += count;
	leftSize -= count;
	count = rtw_sprintf(pstr, leftSize, "\tbit[3]=%d for TRACE\n",
		(GLBtcDbgType[BTC_MSG_ALGORITHM]&ALGO_TRACE)?1:0);
	if ((count < 0) || (count >= leftSize))
		goto exit;
	pstr += count;
	leftSize -= count;
	count = rtw_sprintf(pstr, leftSize, "\tbit[4]=%d for TRACE_FW\n",
		(GLBtcDbgType[BTC_MSG_ALGORITHM]&ALGO_TRACE_FW)?1:0);
	if ((count < 0) || (count >= leftSize))
		goto exit;
	pstr += count;
	leftSize -= count;
	count = rtw_sprintf(pstr, leftSize, "\tbit[5]=%d for TRACE_FW_DETAIL\n",
		(GLBtcDbgType[BTC_MSG_ALGORITHM]&ALGO_TRACE_FW_DETAIL)?1:0);
	if ((count < 0) || (count >= leftSize))
		goto exit;
	pstr += count;
	leftSize -= count;
	count = rtw_sprintf(pstr, leftSize, "\tbit[6]=%d for TRACE_FW_EXEC\n",
		(GLBtcDbgType[BTC_MSG_ALGORITHM]&ALGO_TRACE_FW_EXEC)?1:0);
	if ((count < 0) || (count >= leftSize))
		goto exit;
	pstr += count;
	leftSize -= count;
	count = rtw_sprintf(pstr, leftSize, "\tbit[7]=%d for TRACE_SW\n",
		(GLBtcDbgType[BTC_MSG_ALGORITHM]&ALGO_TRACE_SW)?1:0);
	if ((count < 0) || (count >= leftSize))
		goto exit;
	pstr += count;
	leftSize -= count;
	count = rtw_sprintf(pstr, leftSize, "\tbit[8]=%d for TRACE_SW_DETAIL\n",
		(GLBtcDbgType[BTC_MSG_ALGORITHM]&ALGO_TRACE_SW_DETAIL)?1:0);
	if ((count < 0) || (count >= leftSize))
		goto exit;
	pstr += count;
	leftSize -= count;
	count = rtw_sprintf(pstr, leftSize, "\tbit[9]=%d for TRACE_SW_EXEC\n",
		(GLBtcDbgType[BTC_MSG_ALGORITHM]&ALGO_TRACE_SW_EXEC)?1:0);
	if ((count < 0) || (count >= leftSize))
		goto exit;
	pstr += count;
	leftSize -= count;

exit:
	count = pstr - pStrBuf;
/* 	DBG_871X(FUNC_ADPT_FMT ": usedsize =%d\n", FUNC_ADPT_ARG(padapter), count); */

	return count;
}