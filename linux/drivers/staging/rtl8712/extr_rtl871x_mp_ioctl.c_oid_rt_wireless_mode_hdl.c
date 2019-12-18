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
typedef  int /*<<< orphan*/  u8 ;
struct oid_par_priv {scalar_t__ type_of_oid; int information_buf_len; int* bytes_rw; scalar_t__ information_buf; scalar_t__ adapter_context; } ;
struct TYPE_2__ {int /*<<< orphan*/  wireless_mode; } ;
struct _adapter {TYPE_1__ registrypriv; } ;

/* Variables and functions */
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  RNDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  RNDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  RNDIS_STATUS_SUCCESS ; 
 scalar_t__ SET_OID ; 

uint oid_rt_wireless_mode_hdl(struct oid_par_priv *poid_par_priv)
{
	uint status = RNDIS_STATUS_SUCCESS;
	struct _adapter *Adapter = (struct _adapter *)
				   (poid_par_priv->adapter_context);

	if (poid_par_priv->type_of_oid == SET_OID) {
		if (poid_par_priv->information_buf_len >= sizeof(u8))
			Adapter->registrypriv.wireless_mode =
					*(u8 *)poid_par_priv->information_buf;
		else
			status = RNDIS_STATUS_INVALID_LENGTH;
	} else if (poid_par_priv->type_of_oid == QUERY_OID) {
		if (poid_par_priv->information_buf_len >= sizeof(u8)) {
			*(u8 *)poid_par_priv->information_buf =
					 Adapter->registrypriv.wireless_mode;
			*poid_par_priv->bytes_rw =
					poid_par_priv->information_buf_len;
		} else {
			status = RNDIS_STATUS_INVALID_LENGTH;
		}
	} else {
		status = RNDIS_STATUS_NOT_ACCEPTED;
	}
	return status;
}