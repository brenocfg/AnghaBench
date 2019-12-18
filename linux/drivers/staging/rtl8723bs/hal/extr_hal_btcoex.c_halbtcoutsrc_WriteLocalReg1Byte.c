#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct adapter {int dummy; } ;
struct TYPE_2__ {scalar_t__ chipInterface; struct adapter* Adapter; } ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 scalar_t__ BTC_INTF_SDIO ; 
 int SDIO_LOCAL_BASE ; 
 int /*<<< orphan*/  rtw_write8 (struct adapter*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void halbtcoutsrc_WriteLocalReg1Byte(void *pBtcContext, u32 RegAddr, u8 Data)
{
	PBTC_COEXIST		pBtCoexist = (PBTC_COEXIST)pBtcContext;
	struct adapter *Adapter = pBtCoexist->Adapter;

	if (BTC_INTF_SDIO == pBtCoexist->chipInterface)
		rtw_write8(Adapter, SDIO_LOCAL_BASE | RegAddr, Data);
	else
		rtw_write8(Adapter, RegAddr, Data);
}