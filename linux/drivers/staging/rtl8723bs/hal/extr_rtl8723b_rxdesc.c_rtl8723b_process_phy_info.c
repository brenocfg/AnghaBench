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
typedef  union recv_frame {int dummy; } recv_frame ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  process_link_qual (struct adapter*,union recv_frame*) ; 
 int /*<<< orphan*/  process_rssi (struct adapter*,union recv_frame*) ; 
 int /*<<< orphan*/  rtw_store_phy_info (struct adapter*,void*) ; 

void rtl8723b_process_phy_info(struct adapter *padapter, void *prframe)
{
	union recv_frame *precvframe = prframe;
	/*  */
	/*  Check RSSI */
	/*  */
	process_rssi(padapter, precvframe);
	/*  */
	/*  Check PWDB. */
	/*  */
	/* process_PWDB(padapter, precvframe); */

	/* UpdateRxSignalStatistics8192C(Adapter, pRfd); */
	/*  */
	/*  Check EVM */
	/*  */
	process_link_qual(padapter,  precvframe);
	#ifdef DBG_RX_SIGNAL_DISPLAY_RAW_DATA
	rtw_store_phy_info(padapter, prframe);
	#endif

}