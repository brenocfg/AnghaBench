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
struct adapter {int /*<<< orphan*/  xmitpriv; } ;

/* Variables and functions */
 int GET_8723B_C2H_TX_RPT_LIFE_TIME_OVER (int /*<<< orphan*/ *) ; 
 int GET_8723B_C2H_TX_RPT_RETRY_OVER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RTW_SCTX_DONE_CCX_PKT_FAIL ; 
 int /*<<< orphan*/  RTW_SCTX_DONE_SUCCESS ; 
 int /*<<< orphan*/  rtw_ack_tx_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void CCX_FwC2HTxRpt_8723b(struct adapter *padapter, u8 *pdata, u8 len)
{
	u8 seq_no;

#define	GET_8723B_C2H_TX_RPT_LIFE_TIME_OVER(_Header)	LE_BITS_TO_1BYTE((_Header + 0), 6, 1)
#define	GET_8723B_C2H_TX_RPT_RETRY_OVER(_Header)	LE_BITS_TO_1BYTE((_Header + 0), 7, 1)

	/* DBG_871X("%s, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n", __func__, */
	/* 		*pdata, *(pdata+1), *(pdata+2), *(pdata+3), *(pdata+4), *(pdata+5), *(pdata+6), *(pdata+7)); */

	seq_no = *(pdata+6);

	if (GET_8723B_C2H_TX_RPT_RETRY_OVER(pdata) | GET_8723B_C2H_TX_RPT_LIFE_TIME_OVER(pdata)) {
		rtw_ack_tx_done(&padapter->xmitpriv, RTW_SCTX_DONE_CCX_PKT_FAIL);
	}
/*
	else if (seq_no != padapter->xmitpriv.seq_no) {
		DBG_871X("tx_seq_no =%d, rpt_seq_no =%d\n", padapter->xmitpriv.seq_no, seq_no);
		rtw_ack_tx_done(&padapter->xmitpriv, RTW_SCTX_DONE_CCX_PKT_FAIL);
	}
*/
	else
		rtw_ack_tx_done(&padapter->xmitpriv, RTW_SCTX_DONE_SUCCESS);
}