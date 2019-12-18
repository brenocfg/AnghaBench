#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  privacy_invoked; TYPE_2__* wep_key; int /*<<< orphan*/  wep_index; } ;
struct TYPE_4__ {int /*<<< orphan*/  wpa_enabled; } ;
struct ks_wlan_private {TYPE_3__ reg; TYPE_1__ wpa; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/ * val; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOT11_PRIVACY_INVOKED ; 
 int /*<<< orphan*/  DOT11_WEP_DEFAULT_KEY_ID ; 
 int /*<<< orphan*/  DOT11_WEP_DEFAULT_KEY_VALUE1 ; 
 int /*<<< orphan*/  DOT11_WEP_DEFAULT_KEY_VALUE2 ; 
 int /*<<< orphan*/  DOT11_WEP_DEFAULT_KEY_VALUE3 ; 
 int /*<<< orphan*/  DOT11_WEP_DEFAULT_KEY_VALUE4 ; 
#define  SME_WEP_FLAG_REQUEST 133 
#define  SME_WEP_INDEX_REQUEST 132 
#define  SME_WEP_KEY1_REQUEST 131 
#define  SME_WEP_KEY2_REQUEST 130 
#define  SME_WEP_KEY3_REQUEST 129 
#define  SME_WEP_KEY4_REQUEST 128 
 int /*<<< orphan*/  hostif_mib_set_request_bool (struct ks_wlan_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostif_mib_set_request_int (struct ks_wlan_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostif_mib_set_request_ostring (struct ks_wlan_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hostif_sme_set_wep(struct ks_wlan_private *priv, int type)
{
	switch (type) {
	case SME_WEP_INDEX_REQUEST:
		hostif_mib_set_request_int(priv, DOT11_WEP_DEFAULT_KEY_ID,
					   priv->reg.wep_index);
		break;
	case SME_WEP_KEY1_REQUEST:
		if (priv->wpa.wpa_enabled)
			return;
		hostif_mib_set_request_ostring(priv,
					       DOT11_WEP_DEFAULT_KEY_VALUE1,
					       &priv->reg.wep_key[0].val[0],
					       priv->reg.wep_key[0].size);
		break;
	case SME_WEP_KEY2_REQUEST:
		if (priv->wpa.wpa_enabled)
			return;
		hostif_mib_set_request_ostring(priv,
					       DOT11_WEP_DEFAULT_KEY_VALUE2,
					       &priv->reg.wep_key[1].val[0],
					       priv->reg.wep_key[1].size);
		break;
	case SME_WEP_KEY3_REQUEST:
		if (priv->wpa.wpa_enabled)
			return;
		hostif_mib_set_request_ostring(priv,
					       DOT11_WEP_DEFAULT_KEY_VALUE3,
					       &priv->reg.wep_key[2].val[0],
					       priv->reg.wep_key[2].size);
		break;
	case SME_WEP_KEY4_REQUEST:
		if (priv->wpa.wpa_enabled)
			return;
		hostif_mib_set_request_ostring(priv,
					       DOT11_WEP_DEFAULT_KEY_VALUE4,
					       &priv->reg.wep_key[3].val[0],
					       priv->reg.wep_key[3].size);
		break;
	case SME_WEP_FLAG_REQUEST:
		hostif_mib_set_request_bool(priv, DOT11_PRIVACY_INVOKED,
					    priv->reg.privacy_invoked);
		break;
	}
}