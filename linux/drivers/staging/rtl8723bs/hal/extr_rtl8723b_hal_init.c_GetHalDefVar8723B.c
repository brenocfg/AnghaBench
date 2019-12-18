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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  wifi_spec; } ;
struct adapter {TYPE_1__ registrypriv; } ;
typedef  enum HAL_DEF_VARIABLE { ____Placeholder_HAL_DEF_VARIABLE } HAL_DEF_VARIABLE ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_8192C (char*,int,...) ; 
 int DRVINFO_SZ ; 
 int GetHalDefVar (struct adapter*,int,void*) ; 
#define  HAL_DEF_EXPLICIT_BEAMFORMEE 139 
#define  HAL_DEF_EXPLICIT_BEAMFORMER 138 
#define  HAL_DEF_MACID_SLEEP 137 
#define  HAL_DEF_MAX_RECVBUF_SZ 136 
#define  HAL_DEF_RX_LDPC 135 
#define  HAL_DEF_RX_PACKET_OFFSET 134 
#define  HAL_DEF_RX_STBC 133 
#define  HAL_DEF_TX_LDPC 132 
#define  HAL_DEF_TX_PAGE_BOUNDARY 131 
#define  HAL_DEF_TX_STBC 130 
 int /*<<< orphan*/  HDATA_RATE (int) ; 
#define  HW_DEF_RA_INFO_DUMP 129 
#define  HW_VAR_MAX_RX_AMPDU_FACTOR 128 
 int MAX_AMPDU_FACTOR_16K ; 
 int MAX_RECVBUF_SZ ; 
 int /*<<< orphan*/  REG_HMEBOX_DBG_2_8723B ; 
 int /*<<< orphan*/  RXDESC_SIZE ; 
 int TX_PAGE_BOUNDARY_8723B ; 
 int WMM_NORMAL_TX_PAGE_BOUNDARY_8723B ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rtw_read32 (struct adapter*,int) ; 
 int /*<<< orphan*/  rtw_write32 (struct adapter*,int /*<<< orphan*/ ,int) ; 

u8 GetHalDefVar8723B(struct adapter *padapter, enum HAL_DEF_VARIABLE variable, void *pval)
{
	u8 bResult;

	bResult = _SUCCESS;

	switch (variable) {
	case HAL_DEF_MAX_RECVBUF_SZ:
		*((u32 *)pval) = MAX_RECVBUF_SZ;
		break;

	case HAL_DEF_RX_PACKET_OFFSET:
		*((u32 *)pval) = RXDESC_SIZE + DRVINFO_SZ*8;
		break;

	case HW_VAR_MAX_RX_AMPDU_FACTOR:
		/*  Stanley@BB.SD3 suggests 16K can get stable performance */
		/*  The experiment was done on SDIO interface */
		/*  coding by Lucas@20130730 */
		*(u32 *)pval = MAX_AMPDU_FACTOR_16K;
		break;
	case HAL_DEF_TX_LDPC:
	case HAL_DEF_RX_LDPC:
		*((u8 *)pval) = false;
		break;
	case HAL_DEF_TX_STBC:
		*((u8 *)pval) = 0;
		break;
	case HAL_DEF_RX_STBC:
		*((u8 *)pval) = 1;
		break;
	case HAL_DEF_EXPLICIT_BEAMFORMER:
	case HAL_DEF_EXPLICIT_BEAMFORMEE:
		*((u8 *)pval) = false;
		break;

	case HW_DEF_RA_INFO_DUMP:
		{
			u8 mac_id = *(u8 *)pval;
			u32 cmd;
			u32 ra_info1, ra_info2;
			u32 rate_mask1, rate_mask2;
			u8 curr_tx_rate, curr_tx_sgi, hight_rate, lowest_rate;

			DBG_8192C("============ RA status check  Mac_id:%d ===================\n", mac_id);

			cmd = 0x40000100 | mac_id;
			rtw_write32(padapter, REG_HMEBOX_DBG_2_8723B, cmd);
			msleep(10);
			ra_info1 = rtw_read32(padapter, 0x2F0);
			curr_tx_rate = ra_info1&0x7F;
			curr_tx_sgi = (ra_info1>>7)&0x01;
			DBG_8192C("[ ra_info1:0x%08x ] =>cur_tx_rate = %s, cur_sgi:%d, PWRSTS = 0x%02x \n",
				ra_info1,
				HDATA_RATE(curr_tx_rate),
				curr_tx_sgi,
				(ra_info1>>8)  & 0x07);

			cmd = 0x40000400 | mac_id;
			rtw_write32(padapter, REG_HMEBOX_DBG_2_8723B, cmd);
			msleep(10);
			ra_info1 = rtw_read32(padapter, 0x2F0);
			ra_info2 = rtw_read32(padapter, 0x2F4);
			rate_mask1 = rtw_read32(padapter, 0x2F8);
			rate_mask2 = rtw_read32(padapter, 0x2FC);
			hight_rate = ra_info2&0xFF;
			lowest_rate = (ra_info2>>8)  & 0xFF;

			DBG_8192C("[ ra_info1:0x%08x ] =>RSSI =%d, BW_setting = 0x%02x, DISRA = 0x%02x, VHT_EN = 0x%02x\n",
				ra_info1,
				ra_info1&0xFF,
				(ra_info1>>8)  & 0xFF,
				(ra_info1>>16) & 0xFF,
				(ra_info1>>24) & 0xFF);

			DBG_8192C("[ ra_info2:0x%08x ] =>hight_rate =%s, lowest_rate =%s, SGI = 0x%02x, RateID =%d\n",
				ra_info2,
				HDATA_RATE(hight_rate),
				HDATA_RATE(lowest_rate),
				(ra_info2>>16) & 0xFF,
				(ra_info2>>24) & 0xFF);

			DBG_8192C("rate_mask2 = 0x%08x, rate_mask1 = 0x%08x\n", rate_mask2, rate_mask1);

		}
		break;

	case HAL_DEF_TX_PAGE_BOUNDARY:
		if (!padapter->registrypriv.wifi_spec) {
			*(u8 *)pval = TX_PAGE_BOUNDARY_8723B;
		} else {
			*(u8 *)pval = WMM_NORMAL_TX_PAGE_BOUNDARY_8723B;
		}
		break;

	case HAL_DEF_MACID_SLEEP:
		*(u8 *)pval = true; /*  support macid sleep */
		break;

	default:
		bResult = GetHalDefVar(padapter, variable, pval);
		break;
	}

	return bResult;
}