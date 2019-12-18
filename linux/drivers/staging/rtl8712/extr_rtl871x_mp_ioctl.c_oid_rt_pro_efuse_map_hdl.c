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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u8 ;
struct oid_par_priv {scalar_t__ information_buf_len; scalar_t__ type_of_oid; scalar_t__* bytes_rw; scalar_t__ information_buf; scalar_t__ adapter_context; } ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ EFUSE_MAP_MAX_SIZE ; 
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  RNDIS_STATUS_FAILURE ; 
 int /*<<< orphan*/  RNDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  RNDIS_STATUS_SUCCESS ; 
 scalar_t__ r8712_efuse_map_read (struct _adapter*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ r8712_efuse_map_write (struct _adapter*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ r8712_efuse_reg_init (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_efuse_reg_uninit (struct _adapter*) ; 

uint oid_rt_pro_efuse_map_hdl(struct oid_par_priv *poid_par_priv)
{
	struct _adapter *Adapter = (struct _adapter *)
				   (poid_par_priv->adapter_context);
	uint status = RNDIS_STATUS_SUCCESS;
	u8		*data;

	*poid_par_priv->bytes_rw = 0;
	if (poid_par_priv->information_buf_len < EFUSE_MAP_MAX_SIZE)
		return RNDIS_STATUS_INVALID_LENGTH;
	data = (u8 *)poid_par_priv->information_buf;
	if (poid_par_priv->type_of_oid == QUERY_OID) {
		if (r8712_efuse_map_read(Adapter, 0, EFUSE_MAP_MAX_SIZE, data))
			*poid_par_priv->bytes_rw = EFUSE_MAP_MAX_SIZE;
		else
			status = RNDIS_STATUS_FAILURE;
	} else {
		/* SET_OID */
		if (r8712_efuse_reg_init(Adapter)) {
			if (r8712_efuse_map_write(Adapter, 0,
			    EFUSE_MAP_MAX_SIZE, data))
				*poid_par_priv->bytes_rw = EFUSE_MAP_MAX_SIZE;
			else
				status = RNDIS_STATUS_FAILURE;
			r8712_efuse_reg_uninit(Adapter);
		} else {
			status = RNDIS_STATUS_FAILURE;
		}
	}
	return status;
}