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
struct ipw_priv {TYPE_2__* ieee; } ;
struct TYPE_3__ {int level; int flags; int /*<<< orphan*/  active_key; } ;
struct TYPE_4__ {TYPE_1__ sec; int /*<<< orphan*/  host_mc_decrypt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCT_FLAG_EXT_SECURITY_CCM ; 
 int /*<<< orphan*/  DCT_FLAG_EXT_SECURITY_TKIP ; 
 int /*<<< orphan*/  DCW_WEP_KEY_SEC_TYPE_CCM ; 
 int /*<<< orphan*/  DCW_WEP_KEY_SEC_TYPE_WEP ; 
 int SEC_ACTIVE_KEY ; 
#define  SEC_LEVEL_0 131 
#define  SEC_LEVEL_1 130 
#define  SEC_LEVEL_2 129 
#define  SEC_LEVEL_3 128 
 int /*<<< orphan*/  ipw_send_tgi_tx_key (struct ipw_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_send_wep_keys (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_set_hw_decrypt_multicast (struct ipw_priv*,int) ; 
 int /*<<< orphan*/  ipw_set_hw_decrypt_unicast (struct ipw_priv*,int) ; 

__attribute__((used)) static void ipw_set_hwcrypto_keys(struct ipw_priv *priv)
{
	switch (priv->ieee->sec.level) {
	case SEC_LEVEL_3:
		if (priv->ieee->sec.flags & SEC_ACTIVE_KEY)
			ipw_send_tgi_tx_key(priv,
					    DCT_FLAG_EXT_SECURITY_CCM,
					    priv->ieee->sec.active_key);

		if (!priv->ieee->host_mc_decrypt)
			ipw_send_wep_keys(priv, DCW_WEP_KEY_SEC_TYPE_CCM);
		break;
	case SEC_LEVEL_2:
		if (priv->ieee->sec.flags & SEC_ACTIVE_KEY)
			ipw_send_tgi_tx_key(priv,
					    DCT_FLAG_EXT_SECURITY_TKIP,
					    priv->ieee->sec.active_key);
		break;
	case SEC_LEVEL_1:
		ipw_send_wep_keys(priv, DCW_WEP_KEY_SEC_TYPE_WEP);
		ipw_set_hw_decrypt_unicast(priv, priv->ieee->sec.level);
		ipw_set_hw_decrypt_multicast(priv, priv->ieee->sec.level);
		break;
	case SEC_LEVEL_0:
	default:
		break;
	}
}