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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u32 ;
struct oid_par_priv {scalar_t__ type_of_oid; int information_buf_len; int* bytes_rw; scalar_t__ information_buf; struct _adapter* adapter_context; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_largepacket_crcerr; } ;
struct _adapter {TYPE_1__ recvpriv; } ;

/* Variables and functions */
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  RNDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  RNDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  RNDIS_STATUS_SUCCESS ; 

uint oid_rt_get_large_packet_crc_hdl(struct oid_par_priv *poid_par_priv)
{
	struct _adapter *padapter = poid_par_priv->adapter_context;

	if (poid_par_priv->type_of_oid != QUERY_OID)
		return RNDIS_STATUS_NOT_ACCEPTED;
	if (poid_par_priv->information_buf_len >=  sizeof(u32)) {
		*(u32 *)poid_par_priv->information_buf =
				 padapter->recvpriv.rx_largepacket_crcerr;
		*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;
	} else {
		return RNDIS_STATUS_INVALID_LENGTH;
	}
	return RNDIS_STATUS_SUCCESS;
}