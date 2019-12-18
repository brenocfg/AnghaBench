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
struct oid_par_priv {scalar_t__ type_of_oid; int information_buf_len; scalar_t__ information_buf; struct _adapter* adapter_context; } ;
struct TYPE_3__ {int bcompleted; unsigned long io_offset; int io_value; int /*<<< orphan*/  act_type; } ;
struct TYPE_4__ {int act_in_progress; TYPE_1__ workparam; } ;
struct _adapter {TYPE_2__ mppriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPT_READ_RF ; 
 int /*<<< orphan*/  RNDIS_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  RNDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  RNDIS_STATUS_SUCCESS ; 
 scalar_t__ SET_OID ; 
 scalar_t__ r8712_getrfreg_cmd (struct _adapter*,unsigned char,unsigned char*) ; 

uint oid_rt_pro_rf_read_registry_hdl(struct oid_par_priv *poid_par_priv)
{
	uint status = RNDIS_STATUS_SUCCESS;
	struct _adapter *Adapter = poid_par_priv->adapter_context;

	if (poid_par_priv->type_of_oid != SET_OID) /* QUERY_OID */
		return RNDIS_STATUS_NOT_ACCEPTED;
	if (poid_par_priv->information_buf_len == (sizeof(unsigned long) *
						   3)) {
		if (Adapter->mppriv.act_in_progress) {
			status = RNDIS_STATUS_NOT_ACCEPTED;
		} else {
			/* init workparam */
			Adapter->mppriv.act_in_progress = true;
			Adapter->mppriv.workparam.bcompleted = false;
			Adapter->mppriv.workparam.act_type = MPT_READ_RF;
			Adapter->mppriv.workparam.io_offset = *(unsigned long *)
						poid_par_priv->information_buf;
			Adapter->mppriv.workparam.io_value = 0xcccccccc;

		/* RegOffsetValue	- The offset of RF register to read.
		 * RegDataWidth	- The data width of RF register to read.
		 * RegDataValue	- The value to read.
		 * RegOffsetValue = *((unsigned long *)InformationBuffer);
		 * RegDataWidth = *((unsigned long *)InformationBuffer+1);
		 * RegDataValue =  *((unsigned long *)InformationBuffer+2);
		 */
			if (r8712_getrfreg_cmd(Adapter,
			    *(unsigned char *)poid_par_priv->information_buf,
			    (unsigned char *)&Adapter->mppriv.workparam.io_value
			    ))
				status = RNDIS_STATUS_NOT_ACCEPTED;
		}
	} else {
		status = RNDIS_STATUS_INVALID_LENGTH;
	}
	return status;
}