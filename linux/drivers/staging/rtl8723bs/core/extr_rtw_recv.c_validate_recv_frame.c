#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {int qos; scalar_t__* iv_len; int /*<<< orphan*/  hdrlen; int /*<<< orphan*/  order; int /*<<< orphan*/  privacy; int /*<<< orphan*/  mdata; int /*<<< orphan*/  mfrag; int /*<<< orphan*/  pw_save; int /*<<< orphan*/  seq_num; int /*<<< orphan*/  frag_num; int /*<<< orphan*/  to_fr_ds; } ;
struct TYPE_6__ {scalar_t__* rx_data; struct rx_pkt_attrib attrib; } ;
struct TYPE_7__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct recv_priv {int /*<<< orphan*/  rx_drop; } ;
struct TYPE_9__ {int /*<<< orphan*/  core_rx_pre_unknown; int /*<<< orphan*/  core_rx_pre_data_handled; int /*<<< orphan*/  core_rx_pre_data_err; int /*<<< orphan*/  core_rx_pre_data; int /*<<< orphan*/  core_rx_pre_ctrl_err; int /*<<< orphan*/  core_rx_pre_ctrl; int /*<<< orphan*/  core_rx_pre_mgmt_err; int /*<<< orphan*/  core_rx_pre_mgmt; int /*<<< orphan*/  core_rx_pre_ver_err; } ;
struct adapter {TYPE_4__ rx_logs; struct recv_priv recvpriv; } ;
typedef  int /*<<< orphan*/  sint ;
struct TYPE_8__ {int /*<<< orphan*/  core_rx_pre_mgmt_err_80211w; } ;
struct TYPE_10__ {TYPE_3__ rx_logs; } ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 int /*<<< orphan*/  DBG_871X (char*,scalar_t__) ; 
 int /*<<< orphan*/  DBG_COUNTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetFragNum (scalar_t__*) ; 
 scalar_t__ GetFrameSubType (scalar_t__*) ; 
 scalar_t__ GetFrameType (scalar_t__*) ; 
 int /*<<< orphan*/  GetMData (scalar_t__*) ; 
 int /*<<< orphan*/  GetMFrag (scalar_t__*) ; 
 int /*<<< orphan*/  GetOrder (scalar_t__*) ; 
 int /*<<< orphan*/  GetPrivacy (scalar_t__*) ; 
 int /*<<< orphan*/  GetPwrMgt (scalar_t__*) ; 
 int /*<<< orphan*/  GetSequence (scalar_t__*) ; 
 int /*<<< orphan*/  HAL_DEF_DBG_DUMP_RXPKT ; 
 scalar_t__* LLC_HEADER_SIZE ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
#define  WIFI_CTRL_TYPE 130 
#define  WIFI_DATA_TYPE 129 
#define  WIFI_MGT_TYPE 128 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 int /*<<< orphan*/  dump_rx_packet (scalar_t__*) ; 
 int /*<<< orphan*/  get_tofr_ds (scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (int*,scalar_t__*,int) ; 
 int ntohs (unsigned short) ; 
 TYPE_5__* padapter ; 
 int /*<<< orphan*/  rtw_hal_get_def_var (struct adapter*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  validate_80211w_mgmt (struct adapter*,union recv_frame*) ; 
 int /*<<< orphan*/  validate_recv_ctrl_frame (struct adapter*,union recv_frame*) ; 
 int /*<<< orphan*/  validate_recv_data_frame (struct adapter*,union recv_frame*) ; 
 int /*<<< orphan*/  validate_recv_mgnt_frame (struct adapter*,union recv_frame*) ; 

sint validate_recv_frame(struct adapter *adapter, union recv_frame *precv_frame)
{
	/* shall check frame subtype, to / from ds, da, bssid */

	/* then call check if rx seq/frag. duplicated. */

	u8 type;
	u8 subtype;
	sint retval = _SUCCESS;
	u8 bDumpRxPkt;

	struct rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;

	u8 *ptr = precv_frame->u.hdr.rx_data;
	u8  ver = (unsigned char) (*ptr)&0x3;

	/* add version chk */
	if (ver != 0) {
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("validate_recv_data_frame fail! (ver!= 0)\n"));
		retval = _FAIL;
		DBG_COUNTER(adapter->rx_logs.core_rx_pre_ver_err);
		goto exit;
	}

	type =  GetFrameType(ptr);
	subtype = GetFrameSubType(ptr); /* bit(7)~bit(2) */

	pattrib->to_fr_ds = get_tofr_ds(ptr);

	pattrib->frag_num = GetFragNum(ptr);
	pattrib->seq_num = GetSequence(ptr);

	pattrib->pw_save = GetPwrMgt(ptr);
	pattrib->mfrag = GetMFrag(ptr);
	pattrib->mdata = GetMData(ptr);
	pattrib->privacy = GetPrivacy(ptr);
	pattrib->order = GetOrder(ptr);
	rtw_hal_get_def_var(adapter, HAL_DEF_DBG_DUMP_RXPKT, &(bDumpRxPkt));
	if (bDumpRxPkt == 1) /* dump all rx packets */
		dump_rx_packet(ptr);
	else if ((bDumpRxPkt == 2) && (type == WIFI_MGT_TYPE))
		dump_rx_packet(ptr);
	else if ((bDumpRxPkt == 3) && (type == WIFI_DATA_TYPE))
		dump_rx_packet(ptr);

	switch (type) {
	case WIFI_MGT_TYPE: /* mgnt */
		DBG_COUNTER(adapter->rx_logs.core_rx_pre_mgmt);
		if (validate_80211w_mgmt(adapter, precv_frame) == _FAIL) {
			retval = _FAIL;
			DBG_COUNTER(padapter->rx_logs.core_rx_pre_mgmt_err_80211w);
			break;
		}

		retval = validate_recv_mgnt_frame(adapter, precv_frame);
		if (retval == _FAIL) {
			RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("validate_recv_mgnt_frame fail\n"));
			DBG_COUNTER(adapter->rx_logs.core_rx_pre_mgmt_err);
		}
		retval = _FAIL; /*  only data frame return _SUCCESS */
		break;
	case WIFI_CTRL_TYPE: /* ctrl */
		DBG_COUNTER(adapter->rx_logs.core_rx_pre_ctrl);
		retval = validate_recv_ctrl_frame(adapter, precv_frame);
		if (retval == _FAIL) {
			RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("validate_recv_ctrl_frame fail\n"));
			DBG_COUNTER(adapter->rx_logs.core_rx_pre_ctrl_err);
		}
		retval = _FAIL; /*  only data frame return _SUCCESS */
		break;
	case WIFI_DATA_TYPE: /* data */
		DBG_COUNTER(adapter->rx_logs.core_rx_pre_data);

		pattrib->qos = (subtype & BIT(7)) ? 1:0;
		retval = validate_recv_data_frame(adapter, precv_frame);
		if (retval == _FAIL) {
			struct recv_priv *precvpriv = &adapter->recvpriv;
			/* RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("validate_recv_data_frame fail\n")); */
			precvpriv->rx_drop++;
			DBG_COUNTER(adapter->rx_logs.core_rx_pre_data_err);
		} else if (retval == _SUCCESS) {
#ifdef DBG_RX_DUMP_EAP
			u8 bDumpRxPkt;
			u16 eth_type;

			/*  dump eapol */
			rtw_hal_get_def_var(adapter, HAL_DEF_DBG_DUMP_RXPKT, &(bDumpRxPkt));
			/*  get ether_type */
			memcpy(&eth_type, ptr + pattrib->hdrlen + pattrib->iv_len + LLC_HEADER_SIZE, 2);
			eth_type = ntohs((unsigned short) eth_type);
			if ((bDumpRxPkt == 4) && (eth_type == 0x888e))
				dump_rx_packet(ptr);
#endif
		} else
			DBG_COUNTER(adapter->rx_logs.core_rx_pre_data_handled);
		break;
	default:
		DBG_COUNTER(adapter->rx_logs.core_rx_pre_unknown);
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("validate_recv_data_frame fail! type = 0x%x\n", type));
		#ifdef DBG_RX_DROP_FRAME
		DBG_871X("DBG_RX_DROP_FRAME validate_recv_data_frame fail! type = 0x%x\n", type);
		#endif
		retval = _FAIL;
		break;
	}

exit:
	return retval;
}