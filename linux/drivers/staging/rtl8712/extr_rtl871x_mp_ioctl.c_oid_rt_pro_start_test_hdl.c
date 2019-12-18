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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct oid_par_priv {scalar_t__ type_of_oid; scalar_t__ information_buf; scalar_t__ adapter_context; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;
struct _adapter {TYPE_1__ mppriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  EE_9346CR ; 
 scalar_t__ MSR ; 
 scalar_t__ RCR ; 
 int /*<<< orphan*/  RNDIS_STATUS_NOT_ACCEPTED ; 
 int /*<<< orphan*/  RNDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RXFLTMAP0 ; 
 scalar_t__ SET_OID ; 
 int _9356SEL ; 
 scalar_t__ mp_start_test (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_efuse_change_max_size (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_efuse_reg_init (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_efuse_reg_uninit (struct _adapter*) ; 
 int r8712_read8 (struct _adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_write16 (struct _adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r8712_write8 (struct _adapter*,scalar_t__,int) ; 

uint oid_rt_pro_start_test_hdl(struct oid_par_priv *poid_par_priv)
{
	struct _adapter *Adapter = (struct _adapter *)
				   (poid_par_priv->adapter_context);
	uint status = RNDIS_STATUS_SUCCESS;
	u32 mode;
	u8 val8;

	if (poid_par_priv->type_of_oid != SET_OID)
		return  RNDIS_STATUS_NOT_ACCEPTED;
	mode = *((u32 *)poid_par_priv->information_buf);
	Adapter->mppriv.mode = mode;/* 1 for loopback*/
	if (mp_start_test(Adapter))
		status = RNDIS_STATUS_NOT_ACCEPTED;
	r8712_write8(Adapter, MSR, 1); /* Link in ad hoc network, 0x1025004C */
	r8712_write8(Adapter, RCR, 0); /* RCR : disable all pkt, 0x10250048 */
	/* RCR disable Check BSSID, 0x1025004a */
	r8712_write8(Adapter, RCR + 2, 0x57);
	/* disable RX filter map , mgt frames will put in RX FIFO 0 */
	r8712_write16(Adapter, RXFLTMAP0, 0x0);
	val8 = r8712_read8(Adapter, EE_9346CR);
	if (!(val8 & _9356SEL)) { /*boot from EFUSE*/
		r8712_efuse_reg_init(Adapter);
		r8712_efuse_change_max_size(Adapter);
		r8712_efuse_reg_uninit(Adapter);
	}
	return status;
}