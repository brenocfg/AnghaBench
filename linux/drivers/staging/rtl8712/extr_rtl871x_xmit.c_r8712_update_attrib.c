#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct tx_cmd {int /*<<< orphan*/  txdw1; } ;
struct sta_priv {int dummy; } ;
struct sta_info {int mac_id; scalar_t__ ieee8021x_blocked; } ;
struct security_priv {int /*<<< orphan*/  hw_decrypted; scalar_t__ sw_encrypt; int /*<<< orphan*/  busetkipkey; } ;
struct qos_priv {scalar_t__ qos_option; } ;
struct pkt_file {int pkt_len; } ;
struct pkt_attrib {int ether_type; int pctrl; int pktlen; int dhcp_pkt; int mac_id; int pkt_hdrlen; int priority; int iv_len; int icv_len; int bswenc; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  subtype; int /*<<< orphan*/  hdrlen; scalar_t__ ack_policy; struct sta_info* psta; int /*<<< orphan*/ * ra; int /*<<< orphan*/ * src; int /*<<< orphan*/ * ta; int /*<<< orphan*/ * dst; } ;
struct mlme_priv {int /*<<< orphan*/  dhcp_timer; struct qos_priv qospriv; } ;
struct ethhdr {int /*<<< orphan*/  h_source; int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_proto; } ;
struct TYPE_4__ {scalar_t__ power_mgnt; int /*<<< orphan*/  smart_ps; } ;
struct TYPE_3__ {scalar_t__ pwr_mode; } ;
struct _adapter {struct security_priv securitypriv; TYPE_2__ registrypriv; TYPE_1__ pwrctrlpriv; struct mlme_priv mlmepriv; struct sta_priv stapriv; } ;
typedef  int /*<<< orphan*/  _pkt ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int ETH_HLEN ; 
 int ETH_P_IP ; 
 int /*<<< orphan*/  GET_ENCRY_ALGO (struct security_priv*,struct sta_info*,int /*<<< orphan*/ ,int) ; 
 int QSEL_SHT ; 
 int TXDESC_SIZE ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int /*<<< orphan*/  WIFI_DATA_TYPE ; 
 int /*<<< orphan*/  WIFI_MP_STATE ; 
 int /*<<< orphan*/  WIFI_STATION_STATE ; 
 int /*<<< orphan*/  WLAN_HDR_A3_LEN ; 
#define  _AES_ 131 
 int /*<<< orphan*/  _FAIL ; 
#define  _TKIP_ 130 
#define  _WEP104_ 129 
#define  _WEP40_ 128 
 int /*<<< orphan*/  _r8712_open_pktfile (int /*<<< orphan*/ *,struct pkt_file*) ; 
 int /*<<< orphan*/  _r8712_pktfile_read (struct pkt_file*,...) ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_bssid (struct mlme_priv*) ; 
 int is_multicast_ether_addr (int /*<<< orphan*/ *) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 struct sta_info* r8712_get_bcmc_stainfo (struct _adapter*) ; 
 struct sta_info* r8712_get_stainfo (struct sta_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r8712_set_ps_mode (struct _adapter*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_set_qos (struct pkt_file*,struct pkt_attrib*) ; 

int r8712_update_attrib(struct _adapter *padapter, _pkt *pkt,
			struct pkt_attrib *pattrib)
{
	struct pkt_file pktfile;
	struct sta_info *psta = NULL;
	struct ethhdr etherhdr;

	struct tx_cmd txdesc;

	bool bmcast;
	struct sta_priv		*pstapriv = &padapter->stapriv;
	struct security_priv	*psecuritypriv = &padapter->securitypriv;
	struct mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	struct qos_priv		*pqospriv = &pmlmepriv->qospriv;

	_r8712_open_pktfile(pkt, &pktfile);

	_r8712_pktfile_read(&pktfile, (unsigned char *)&etherhdr, ETH_HLEN);

	pattrib->ether_type = ntohs(etherhdr.h_proto);

	/*
	 * If driver xmit ARP packet, driver can set ps mode to initial
	 * setting. It stands for getting DHCP or fix IP.
	 */
	if (pattrib->ether_type == 0x0806) {
		if (padapter->pwrctrlpriv.pwr_mode !=
		    padapter->registrypriv.power_mgnt) {
			del_timer_sync(&pmlmepriv->dhcp_timer);
			r8712_set_ps_mode(padapter,
					  padapter->registrypriv.power_mgnt,
					  padapter->registrypriv.smart_ps);
		}
	}

	memcpy(pattrib->dst, &etherhdr.h_dest, ETH_ALEN);
	memcpy(pattrib->src, &etherhdr.h_source, ETH_ALEN);
	pattrib->pctrl = 0;
	if (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) ||
	    check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) {
		memcpy(pattrib->ra, pattrib->dst, ETH_ALEN);
		memcpy(pattrib->ta, pattrib->src, ETH_ALEN);
	} else if (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) {
		memcpy(pattrib->ra, get_bssid(pmlmepriv), ETH_ALEN);
		memcpy(pattrib->ta, pattrib->src, ETH_ALEN);
	} else if (check_fwstate(pmlmepriv, WIFI_AP_STATE)) {
		memcpy(pattrib->ra, pattrib->dst, ETH_ALEN);
		memcpy(pattrib->ta, get_bssid(pmlmepriv), ETH_ALEN);
	} else if (check_fwstate(pmlmepriv, WIFI_MP_STATE)) {
		/*firstly, filter packet not belongs to mp*/
		if (pattrib->ether_type != 0x8712)
			return -EINVAL;
		/* for mp storing the txcmd per packet,
		 * according to the info of txcmd to update pattrib
		 */
		/*get MP_TXDESC_SIZE bytes txcmd per packet*/
		_r8712_pktfile_read(&pktfile, (u8 *)&txdesc, TXDESC_SIZE);
		memcpy(pattrib->ra, pattrib->dst, ETH_ALEN);
		memcpy(pattrib->ta, pattrib->src, ETH_ALEN);
		pattrib->pctrl = 1;
	}
	/* r8712_xmitframe_coalesce() overwrite this!*/
	pattrib->pktlen = pktfile.pkt_len;
	if (pattrib->ether_type == ETH_P_IP) {
		/* The following is for DHCP and ARP packet, we use cck1M to
		 * tx these packets and let LPS awake some time
		 * to prevent DHCP protocol fail
		 */
		u8 tmp[24];

		_r8712_pktfile_read(&pktfile, &tmp[0], 24);
		pattrib->dhcp_pkt = 0;
		if (pktfile.pkt_len > 282) {/*MINIMUM_DHCP_PACKET_SIZE)*/
			if (pattrib->ether_type == ETH_P_IP) {/* IP header*/
				if (((tmp[21] == 68) && (tmp[23] == 67)) ||
					((tmp[21] == 67) && (tmp[23] == 68))) {
					/* 68 : UDP BOOTP client
					 * 67 : UDP BOOTP server
					 * Use low rate to send DHCP packet.
					 */
					pattrib->dhcp_pkt = 1;
				}
			}
		}
	}
	bmcast = is_multicast_ether_addr(pattrib->ra);
	/* get sta_info*/
	if (bmcast) {
		psta = r8712_get_bcmc_stainfo(padapter);
		pattrib->mac_id = 4;
	} else {
		if (check_fwstate(pmlmepriv, WIFI_MP_STATE)) {
			psta = r8712_get_stainfo(pstapriv,
						 get_bssid(pmlmepriv));
			pattrib->mac_id = 5;
		} else {
			psta = r8712_get_stainfo(pstapriv, pattrib->ra);
			if (psta == NULL)  /* drop the pkt */
				return -ENOMEM;
			if (check_fwstate(pmlmepriv, WIFI_STATION_STATE))
				pattrib->mac_id = 5;
			else
				pattrib->mac_id = psta->mac_id;
		}
	}

	if (psta) {
		pattrib->psta = psta;
	} else {
		/* if we cannot get psta => drrp the pkt */
		return -ENOMEM;
	}

	pattrib->ack_policy = 0;
	/* get ether_hdr_len */
	pattrib->pkt_hdrlen = ETH_HLEN;

	if (pqospriv->qos_option) {
		r8712_set_qos(&pktfile, pattrib);
	} else {
		pattrib->hdrlen = WLAN_HDR_A3_LEN;
		pattrib->subtype = WIFI_DATA_TYPE;
		pattrib->priority = 0;
	}
	if (psta->ieee8021x_blocked) {
		pattrib->encrypt = 0;
		if ((pattrib->ether_type != 0x888e) &&
		    !check_fwstate(pmlmepriv, WIFI_MP_STATE))
			return -EINVAL;
	} else {
		GET_ENCRY_ALGO(psecuritypriv, psta, pattrib->encrypt, bmcast);
	}
	switch (pattrib->encrypt) {
	case _WEP40_:
	case _WEP104_:
		pattrib->iv_len = 4;
		pattrib->icv_len = 4;
		break;
	case _TKIP_:
		pattrib->iv_len = 8;
		pattrib->icv_len = 4;
		if (padapter->securitypriv.busetkipkey == _FAIL)
			return -EINVAL;
		break;
	case _AES_:
		pattrib->iv_len = 8;
		pattrib->icv_len = 8;
		break;
	default:
		pattrib->iv_len = 0;
		pattrib->icv_len = 0;
		break;
	}

	if (pattrib->encrypt &&
	    (padapter->securitypriv.sw_encrypt ||
	    !psecuritypriv->hw_decrypted))
		pattrib->bswenc = true;
	else
		pattrib->bswenc = false;
	/* if in MP_STATE, update pkt_attrib from mp_txcmd, and overwrite
	 * some settings above.
	 */
	if (check_fwstate(pmlmepriv, WIFI_MP_STATE))
		pattrib->priority =
		    (le32_to_cpu(txdesc.txdw1) >> QSEL_SHT) & 0x1f;
	return 0;
}