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
typedef  scalar_t__ u8 ;
struct registry_priv {int rf_config; int mp_mode; int wifi_test; int /*<<< orphan*/  low_power; int /*<<< orphan*/  vcs_type; int /*<<< orphan*/  vrtl_carrier_sense; int /*<<< orphan*/  cbw40_enable; } ;
struct fw_priv {int mp_mode; int turbo_mode; int /*<<< orphan*/  low_power_mode; int /*<<< orphan*/  vcs_mode; int /*<<< orphan*/  vcs_type; int /*<<< orphan*/  rf_config; int /*<<< orphan*/  bw_40MHz_en; scalar_t__ usb_ep_num; int /*<<< orphan*/  hci_sel; } ;
struct dvobj_priv {scalar_t__ nr_endpoint; } ;
struct _adapter {struct registry_priv registrypriv; struct dvobj_priv dvobjpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8712_HCI_TYPE_72USB ; 
 int /*<<< orphan*/  RTL8712_RFC_1T1R ; 
 int /*<<< orphan*/  RTL8712_RFC_1T2R ; 
 int /*<<< orphan*/  RTL8712_RFC_2T2R ; 
#define  RTL8712_RF_1T1R 130 
#define  RTL8712_RF_1T2R 129 
#define  RTL8712_RF_2T2R 128 
 int /*<<< orphan*/  memset (struct fw_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fill_fwpriv(struct _adapter *adapter, struct fw_priv *fwpriv)
{
	struct dvobj_priv *dvobj = &adapter->dvobjpriv;
	struct registry_priv *regpriv = &adapter->registrypriv;

	memset(fwpriv, 0, sizeof(struct fw_priv));
	/* todo: check if needs endian conversion */
	fwpriv->hci_sel =  RTL8712_HCI_TYPE_72USB;
	fwpriv->usb_ep_num = (u8)dvobj->nr_endpoint;
	fwpriv->bw_40MHz_en = regpriv->cbw40_enable;
	switch (regpriv->rf_config) {
	case RTL8712_RF_1T1R:
		fwpriv->rf_config = RTL8712_RFC_1T1R;
		break;
	case RTL8712_RF_2T2R:
		fwpriv->rf_config = RTL8712_RFC_2T2R;
		break;
	case RTL8712_RF_1T2R:
	default:
		fwpriv->rf_config = RTL8712_RFC_1T2R;
	}
	fwpriv->mp_mode = (regpriv->mp_mode == 1) ? 1 : 0;
	/* 0:off 1:on 2:auto */
	fwpriv->vcs_type = regpriv->vrtl_carrier_sense;
	fwpriv->vcs_mode = regpriv->vcs_type; /* 1:RTS/CTS 2:CTS to self */
	/* default enable turbo_mode */
	fwpriv->turbo_mode = ((regpriv->wifi_test == 1) ? 0 : 1);
	fwpriv->low_power_mode = regpriv->low_power;
}