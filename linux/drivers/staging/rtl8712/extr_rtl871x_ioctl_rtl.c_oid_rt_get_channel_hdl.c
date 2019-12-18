#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u32 ;
struct oid_par_priv {scalar_t__ type_of_oid; int /*<<< orphan*/  information_buf_len; int /*<<< orphan*/ * bytes_rw; scalar_t__ information_buf; struct _adapter* adapter_context; } ;
struct NDIS_802_11_CONFIGURATION {int /*<<< orphan*/  DSConfig; } ;
struct TYPE_5__ {struct NDIS_802_11_CONFIGURATION Configuration; } ;
struct TYPE_6__ {TYPE_1__ network; } ;
struct mlme_priv {TYPE_2__ cur_network; } ;
struct TYPE_7__ {struct NDIS_802_11_CONFIGURATION Configuration; } ;
struct TYPE_8__ {TYPE_3__ dev_network; } ;
struct _adapter {TYPE_4__ registrypriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  RNDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  RNDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 

uint oid_rt_get_channel_hdl(struct oid_par_priv *poid_par_priv)
{
	struct _adapter *padapter = poid_par_priv->adapter_context;
	struct	mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct NDIS_802_11_CONFIGURATION *pnic_Config;
	u32   channelnum;

	if (poid_par_priv->type_of_oid != QUERY_OID)
		return RNDIS_STATUS_NOT_ACCEPTED;
	if (check_fwstate(pmlmepriv, _FW_LINKED) ||
	    check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE))
		pnic_Config = &pmlmepriv->cur_network.network.Configuration;
	else
		pnic_Config = &padapter->registrypriv.dev_network.Configuration;
	channelnum = pnic_Config->DSConfig;
	*(u32 *)poid_par_priv->information_buf = channelnum;
	*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;
	return RNDIS_STATUS_SUCCESS;
}