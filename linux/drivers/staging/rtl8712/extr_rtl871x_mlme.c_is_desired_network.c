#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {scalar_t__ Privacy; scalar_t__ InfrastructureMode; int /*<<< orphan*/  IELength; int /*<<< orphan*/  IEs; } ;
struct wlan_network {TYPE_1__ network; } ;
struct security_priv {scalar_t__ PrivacyAlgrthm; scalar_t__ wps_phase; } ;
struct TYPE_6__ {scalar_t__ InfrastructureMode; } ;
struct TYPE_7__ {TYPE_2__ network; } ;
struct TYPE_8__ {TYPE_3__ cur_network; } ;
struct _adapter {TYPE_4__ mlmepriv; struct security_priv securitypriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 scalar_t__ _NO_PRIVACY_ ; 
 scalar_t__ check_fwstate (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ r8712_get_wps_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int is_desired_network(struct _adapter *adapter,
				struct wlan_network *pnetwork)
{
	u8 wps_ie[512];
	uint wps_ielen;
	int bselected = true;
	struct	security_priv *psecuritypriv = &adapter->securitypriv;

	if (psecuritypriv->wps_phase) {
		if (r8712_get_wps_ie(pnetwork->network.IEs,
		    pnetwork->network.IELength, wps_ie,
		    &wps_ielen))
			return true;
		return false;
	}
	if ((psecuritypriv->PrivacyAlgrthm != _NO_PRIVACY_) &&
		    (pnetwork->network.Privacy == 0))
		bselected = false;
	if (check_fwstate(&adapter->mlmepriv, WIFI_ADHOC_STATE)) {
		if (pnetwork->network.InfrastructureMode !=
			adapter->mlmepriv.cur_network.network.
			InfrastructureMode)
			bselected = false;
	}
	return bselected;
}