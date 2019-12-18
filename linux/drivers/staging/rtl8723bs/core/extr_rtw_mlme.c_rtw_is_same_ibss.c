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
struct TYPE_2__ {int Privacy; } ;
struct wlan_network {TYPE_1__ network; } ;
struct security_priv {scalar_t__ dot11PrivacyAlgrthm; } ;
struct adapter {struct security_priv securitypriv; } ;

/* Variables and functions */
 scalar_t__ _NO_PRIVACY_ ; 

int rtw_is_same_ibss(struct adapter *adapter, struct wlan_network *pnetwork)
{
	int ret = true;
	struct security_priv *psecuritypriv = &adapter->securitypriv;

	if ((psecuritypriv->dot11PrivacyAlgrthm != _NO_PRIVACY_) &&
		    (pnetwork->network.Privacy == 0))
		ret = false;
	else if ((psecuritypriv->dot11PrivacyAlgrthm == _NO_PRIVACY_) &&
		 (pnetwork->network.Privacy == 1))
		ret = false;
	else
		ret = true;

	return ret;

}