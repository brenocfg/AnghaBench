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
struct debug_priv {scalar_t__ dbg_rx_fifo_last_overflow; scalar_t__ dbg_rx_fifo_curr_overflow; scalar_t__ dbg_rx_fifo_diff_overflow; } ;
struct dvobj_priv {struct debug_priv drv_dbg; } ;
struct adapter {struct dvobj_priv* dvobj; } ;

/* Variables and functions */
 scalar_t__ REG_RXERR_RPT ; 
 scalar_t__ rtw_read16 (struct adapter*,scalar_t__) ; 
 int rtw_read8 (struct adapter*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_write8 (struct adapter*,scalar_t__,int) ; 

void rtw_hal_check_rxfifo_full(struct adapter *adapter)
{
	struct dvobj_priv *psdpriv = adapter->dvobj;
	struct debug_priv *pdbgpriv = &psdpriv->drv_dbg;
	int save_cnt = false;

	/* switch counter to RX fifo */
	/* printk("8723b or 8192e , MAC_667 set 0xf0\n"); */
	rtw_write8(adapter, REG_RXERR_RPT+3, rtw_read8(adapter, REG_RXERR_RPT+3)|0xf0);
	save_cnt = true;
	/* todo: other chips */

	if (save_cnt) {
		/* rtw_write8(adapter, REG_RXERR_RPT+3, rtw_read8(adapter, REG_RXERR_RPT+3)|0xa0); */
		pdbgpriv->dbg_rx_fifo_last_overflow = pdbgpriv->dbg_rx_fifo_curr_overflow;
		pdbgpriv->dbg_rx_fifo_curr_overflow = rtw_read16(adapter, REG_RXERR_RPT);
		pdbgpriv->dbg_rx_fifo_diff_overflow = pdbgpriv->dbg_rx_fifo_curr_overflow-pdbgpriv->dbg_rx_fifo_last_overflow;
	}
}