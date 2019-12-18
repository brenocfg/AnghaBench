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
struct TYPE_2__ {scalar_t__ length; } ;
union iwreq_data {TYPE_1__ data; } ;
struct rtllib_device {scalar_t__ wpa_ie_len; int /*<<< orphan*/ * wpa_ie; } ;
struct r8192_priv {struct rtllib_device* rtllib; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int E2BIG ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,scalar_t__) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static int _rtl92e_wx_get_gen_ie(struct net_device *dev,
				 struct iw_request_info *info,
				 union iwreq_data *data, char *extra)
{
	int ret = 0;
	struct r8192_priv *priv = rtllib_priv(dev);
	struct rtllib_device *ieee = priv->rtllib;

	if (ieee->wpa_ie_len == 0 || ieee->wpa_ie == NULL) {
		data->data.length = 0;
		return 0;
	}

	if (data->data.length < ieee->wpa_ie_len)
		return -E2BIG;

	data->data.length = ieee->wpa_ie_len;
	memcpy(extra, ieee->wpa_ie, ieee->wpa_ie_len);
	return ret;
}