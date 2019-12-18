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
typedef  int /*<<< orphan*/  u16 ;
struct oid_par_priv {scalar_t__ type_of_oid; scalar_t__ information_buf; struct _adapter* adapter_context; } ;
struct eeprom_priv {int /*<<< orphan*/  channel_plan; } ;
struct _adapter {struct eeprom_priv eeprompriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RNDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  RNDIS_STATUS_SUCCESS ; 
 scalar_t__ SET_OID ; 

uint oid_rt_set_channelplan_hdl(struct oid_par_priv
				       *poid_par_priv)
{
	struct _adapter *padapter = poid_par_priv->adapter_context;
	struct eeprom_priv *peeprompriv = &padapter->eeprompriv;

	if (poid_par_priv->type_of_oid != SET_OID)
		return RNDIS_STATUS_NOT_ACCEPTED;
	peeprompriv->channel_plan = *(u16 *)poid_par_priv->information_buf;
	return RNDIS_STATUS_SUCCESS;
}