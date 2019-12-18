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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct tx_desc {int dummy; } ;
struct TYPE_2__ {int dot11PrivacyAlgrthm; } ;
struct adapter {TYPE_1__ securitypriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC8723B_RATE1M ; 
 int /*<<< orphan*/  QSLT_MGNT ; 
 int /*<<< orphan*/  SET_TX_DESC_BT_INT_8723B (scalar_t__*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_FIRST_SEG_8723B (scalar_t__*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_HWSEQ_EN_8723B (scalar_t__*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_HWSEQ_SEL_8723B (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_LAST_SEG_8723B (scalar_t__*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_NAV_USE_HDR_8723B (scalar_t__*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_OFFSET_8723B (scalar_t__*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_OWN_8723B (scalar_t__*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_PKT_SIZE_8723B (scalar_t__*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_QUEUE_SEL_8723B (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_SEC_TYPE_8723B (scalar_t__*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_RATE_8723B (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_USE_RATE_8723B (scalar_t__*,int) ; 
 int /*<<< orphan*/  TXDESC_SIZE ; 
#define  _AES_ 133 
#define  _NO_PRIVACY_ 132 
#define  _SMS4_ 131 
#define  _TKIP_ 130 
#define  _WEP104_ 129 
#define  _WEP40_ 128 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8723b_cal_txdesc_chksum (struct tx_desc*) ; 

void rtl8723b_fill_fake_txdesc(
	struct adapter *padapter,
	u8 *pDesc,
	u32 BufferLen,
	u8 IsPsPoll,
	u8 IsBTQosNull,
	u8 bDataFrame
)
{
	/*  Clear all status */
	memset(pDesc, 0, TXDESC_SIZE);

	SET_TX_DESC_FIRST_SEG_8723B(pDesc, 1); /* bFirstSeg; */
	SET_TX_DESC_LAST_SEG_8723B(pDesc, 1); /* bLastSeg; */

	SET_TX_DESC_OFFSET_8723B(pDesc, 0x28); /*  Offset = 32 */

	SET_TX_DESC_PKT_SIZE_8723B(pDesc, BufferLen); /*  Buffer size + command header */
	SET_TX_DESC_QUEUE_SEL_8723B(pDesc, QSLT_MGNT); /*  Fixed queue of Mgnt queue */

	/*  Set NAVUSEHDR to prevent Ps-poll AId filed to be changed to error vlaue by Hw. */
	if (IsPsPoll) {
		SET_TX_DESC_NAV_USE_HDR_8723B(pDesc, 1);
	} else {
		SET_TX_DESC_HWSEQ_EN_8723B(pDesc, 1); /*  Hw set sequence number */
		SET_TX_DESC_HWSEQ_SEL_8723B(pDesc, 0);
	}

	if (IsBTQosNull) {
		SET_TX_DESC_BT_INT_8723B(pDesc, 1);
	}

	SET_TX_DESC_USE_RATE_8723B(pDesc, 1); /*  use data rate which is set by Sw */
	SET_TX_DESC_OWN_8723B((u8 *)pDesc, 1);

	SET_TX_DESC_TX_RATE_8723B(pDesc, DESC8723B_RATE1M);

	/*  */
	/*  Encrypt the data frame if under security mode excepct null data. Suggested by CCW. */
	/*  */
	if (bDataFrame) {
		u32 EncAlg;

		EncAlg = padapter->securitypriv.dot11PrivacyAlgrthm;
		switch (EncAlg) {
		case _NO_PRIVACY_:
			SET_TX_DESC_SEC_TYPE_8723B(pDesc, 0x0);
			break;
		case _WEP40_:
		case _WEP104_:
		case _TKIP_:
			SET_TX_DESC_SEC_TYPE_8723B(pDesc, 0x1);
			break;
		case _SMS4_:
			SET_TX_DESC_SEC_TYPE_8723B(pDesc, 0x2);
			break;
		case _AES_:
			SET_TX_DESC_SEC_TYPE_8723B(pDesc, 0x3);
			break;
		default:
			SET_TX_DESC_SEC_TYPE_8723B(pDesc, 0x0);
			break;
		}
	}

	/*  USB interface drop packet if the checksum of descriptor isn't correct. */
	/*  Using this checksum can let hardware recovery from packet bulk out error (e.g. Cancel URC, Bulk out error.). */
	rtl8723b_cal_txdesc_chksum((struct tx_desc *)pDesc);
}