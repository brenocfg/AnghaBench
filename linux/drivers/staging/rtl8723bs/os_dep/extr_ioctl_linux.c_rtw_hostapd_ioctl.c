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
struct net_device {int dummy; } ;
struct iw_point {int /*<<< orphan*/  length; int /*<<< orphan*/  pointer; } ;
struct ieee_param {int cmd; } ;
struct adapter {int /*<<< orphan*/  hw_init_completed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,int) ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
#define  RTL871X_HOSTAPD_ACL_ADD_STA 141 
#define  RTL871X_HOSTAPD_ACL_REMOVE_STA 140 
#define  RTL871X_HOSTAPD_ADD_STA 139 
#define  RTL871X_HOSTAPD_FLUSH 138 
#define  RTL871X_HOSTAPD_GET_INFO_STA 137 
#define  RTL871X_HOSTAPD_GET_WPAIE_STA 136 
#define  RTL871X_HOSTAPD_REMOVE_STA 135 
#define  RTL871X_HOSTAPD_SET_BEACON 134 
#define  RTL871X_HOSTAPD_SET_HIDDEN_SSID 133 
#define  RTL871X_HOSTAPD_SET_MACADDR_ACL 132 
#define  RTL871X_HOSTAPD_SET_WPS_ASSOC_RESP 131 
#define  RTL871X_HOSTAPD_SET_WPS_BEACON 130 
#define  RTL871X_HOSTAPD_SET_WPS_PROBE_RESP 129 
#define  RTL871X_SET_ENCRYPTION 128 
 scalar_t__ copy_from_user (struct ieee_param*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct ieee_param*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ieee_param*) ; 
 int rtw_add_sta (struct net_device*,struct ieee_param*) ; 
 int rtw_del_sta (struct net_device*,struct ieee_param*) ; 
 int rtw_get_sta_wpaie (struct net_device*,struct ieee_param*) ; 
 int /*<<< orphan*/  rtw_hostapd_sta_flush (struct net_device*) ; 
 int rtw_ioctl_acl_add_sta (struct net_device*,struct ieee_param*,int /*<<< orphan*/ ) ; 
 int rtw_ioctl_acl_remove_sta (struct net_device*,struct ieee_param*,int /*<<< orphan*/ ) ; 
 int rtw_ioctl_get_sta_data (struct net_device*,struct ieee_param*,int /*<<< orphan*/ ) ; 
 int rtw_ioctl_set_macaddr_acl (struct net_device*,struct ieee_param*,int /*<<< orphan*/ ) ; 
 struct ieee_param* rtw_malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 int rtw_set_beacon (struct net_device*,struct ieee_param*,int /*<<< orphan*/ ) ; 
 int rtw_set_encryption (struct net_device*,struct ieee_param*,int /*<<< orphan*/ ) ; 
 int rtw_set_hidden_ssid (struct net_device*,struct ieee_param*,int /*<<< orphan*/ ) ; 
 int rtw_set_wps_assoc_resp (struct net_device*,struct ieee_param*,int /*<<< orphan*/ ) ; 
 int rtw_set_wps_beacon (struct net_device*,struct ieee_param*,int /*<<< orphan*/ ) ; 
 int rtw_set_wps_probe_resp (struct net_device*,struct ieee_param*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtw_hostapd_ioctl(struct net_device *dev, struct iw_point *p)
{
	struct ieee_param *param;
	int ret = 0;
	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(dev);

	/* DBG_871X("%s\n", __func__); */

	/*
	* this function is expect to call in master mode, which allows no power saving
	* so, we just check hw_init_completed
	*/

	if (!padapter->hw_init_completed) {
		ret = -EPERM;
		goto out;
	}


	/* if (p->length < sizeof(struct ieee_param) || !p->pointer) { */
	if (!p->pointer) {
		ret = -EINVAL;
		goto out;
	}

	param = rtw_malloc(p->length);
	if (param == NULL) {
		ret = -ENOMEM;
		goto out;
	}

	if (copy_from_user(param, p->pointer, p->length)) {
		kfree(param);
		ret = -EFAULT;
		goto out;
	}

	/* DBG_871X("%s, cmd =%d\n", __func__, param->cmd); */

	switch (param->cmd) {
	case RTL871X_HOSTAPD_FLUSH:

		rtw_hostapd_sta_flush(dev);

		break;

	case RTL871X_HOSTAPD_ADD_STA:

		ret = rtw_add_sta(dev, param);

		break;

	case RTL871X_HOSTAPD_REMOVE_STA:

		ret = rtw_del_sta(dev, param);

		break;

	case RTL871X_HOSTAPD_SET_BEACON:

		ret = rtw_set_beacon(dev, param, p->length);

		break;

	case RTL871X_SET_ENCRYPTION:

		ret = rtw_set_encryption(dev, param, p->length);

		break;

	case RTL871X_HOSTAPD_GET_WPAIE_STA:

		ret = rtw_get_sta_wpaie(dev, param);

		break;

	case RTL871X_HOSTAPD_SET_WPS_BEACON:

		ret = rtw_set_wps_beacon(dev, param, p->length);

		break;

	case RTL871X_HOSTAPD_SET_WPS_PROBE_RESP:

		ret = rtw_set_wps_probe_resp(dev, param, p->length);

		break;

	case RTL871X_HOSTAPD_SET_WPS_ASSOC_RESP:

		ret = rtw_set_wps_assoc_resp(dev, param, p->length);

		break;

	case RTL871X_HOSTAPD_SET_HIDDEN_SSID:

		ret = rtw_set_hidden_ssid(dev, param, p->length);

		break;

	case RTL871X_HOSTAPD_GET_INFO_STA:

		ret = rtw_ioctl_get_sta_data(dev, param, p->length);

		break;

	case RTL871X_HOSTAPD_SET_MACADDR_ACL:

		ret = rtw_ioctl_set_macaddr_acl(dev, param, p->length);

		break;

	case RTL871X_HOSTAPD_ACL_ADD_STA:

		ret = rtw_ioctl_acl_add_sta(dev, param, p->length);

		break;

	case RTL871X_HOSTAPD_ACL_REMOVE_STA:

		ret = rtw_ioctl_acl_remove_sta(dev, param, p->length);

		break;

	default:
		DBG_871X("Unknown hostapd request: %d\n", param->cmd);
		ret = -EOPNOTSUPP;
		break;

	}

	if (ret == 0 && copy_to_user(p->pointer, param, p->length))
		ret = -EFAULT;


	kfree(param);

out:

	return ret;

}