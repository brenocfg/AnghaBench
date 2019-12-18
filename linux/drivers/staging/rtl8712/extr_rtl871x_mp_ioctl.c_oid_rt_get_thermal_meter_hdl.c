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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct oid_par_priv {scalar_t__ type_of_oid; int information_buf_len; int* bytes_rw; scalar_t__ information_buf; scalar_t__ adapter_context; } ;
struct TYPE_3__ {int bcompleted; int io_value; scalar_t__ io_offset; int /*<<< orphan*/  act_type; } ;
struct TYPE_4__ {int act_in_progress; TYPE_1__ workparam; } ;
struct _adapter {TYPE_2__ mppriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPT_GET_THERMAL_METER ; 
 scalar_t__ QUERY_OID ; 
 int /*<<< orphan*/  RNDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  RNDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  RNDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  r8712_GetThermalMeter (struct _adapter*,int*) ; 

uint oid_rt_get_thermal_meter_hdl(struct oid_par_priv *poid_par_priv)
{
	struct _adapter *Adapter = (struct _adapter *)
				   (poid_par_priv->adapter_context);

	if (poid_par_priv->type_of_oid != QUERY_OID)
		return RNDIS_STATUS_NOT_ACCEPTED;

	if (Adapter->mppriv.act_in_progress)
		return RNDIS_STATUS_NOT_ACCEPTED;

	if (poid_par_priv->information_buf_len < sizeof(u8))
		return RNDIS_STATUS_INVALID_LENGTH;
	/*init workparam*/
	Adapter->mppriv.act_in_progress = true;
	Adapter->mppriv.workparam.bcompleted = false;
	Adapter->mppriv.workparam.act_type = MPT_GET_THERMAL_METER;
	Adapter->mppriv.workparam.io_offset = 0;
	Adapter->mppriv.workparam.io_value = 0xFFFFFFFF;
	r8712_GetThermalMeter(Adapter, &Adapter->mppriv.workparam.io_value);
	Adapter->mppriv.workparam.bcompleted = true;
	Adapter->mppriv.act_in_progress = false;
	*(u32 *)poid_par_priv->information_buf =
				 Adapter->mppriv.workparam.io_value;
	*poid_par_priv->bytes_rw = sizeof(u32);
	return RNDIS_STATUS_SUCCESS;
}