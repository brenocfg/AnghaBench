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
typedef  int u8 ;
struct registry_priv {scalar_t__ wifi_spec; } ;
struct adapter {struct registry_priv registrypriv; } ;

/* Variables and functions */
 scalar_t__ REG_RXDMA_AGG_PG_TH ; 
 int /*<<< orphan*/  rtw_write8 (struct adapter*,scalar_t__,int) ; 

__attribute__((used)) static void HalRxAggr8723BSdio(struct adapter *padapter)
{
	struct registry_priv *pregistrypriv;
	u8 valueDMATimeout;
	u8 valueDMAPageCount;


	pregistrypriv = &padapter->registrypriv;

	if (pregistrypriv->wifi_spec) {
		/*  2010.04.27 hpfan */
		/*  Adjust RxAggrTimeout to close to zero disable RxAggr, suggested by designer */
		/*  Timeout value is calculated by 34 / (2^n) */
		valueDMATimeout = 0x06;
		valueDMAPageCount = 0x06;
	} else {
		/*  20130530, Isaac@SD1 suggest 3 kinds of parameter */
		/*  TX/RX Balance */
		valueDMATimeout = 0x06;
		valueDMAPageCount = 0x06;
	}

	rtw_write8(padapter, REG_RXDMA_AGG_PG_TH + 1, valueDMATimeout);
	rtw_write8(padapter, REG_RXDMA_AGG_PG_TH, valueDMAPageCount);
}