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
struct TYPE_4__ {scalar_t__ length; } ;
union iwreq_data {TYPE_2__ data; } ;
struct TYPE_3__ {int bPromiscuousOn; int bFilterSourceStationFrame; } ;
struct rtllib_device {TYPE_1__ IntelPromiscuousModeInfo; } ;
struct r8192_priv {int /*<<< orphan*/  wx_mutex; struct rtllib_device* rtllib; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int _rtl92e_wx_get_promisc_mode(struct net_device *dev,
				       struct iw_request_info *info,
				       union iwreq_data *wrqu, char *extra)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	struct rtllib_device *ieee = priv->rtllib;

	mutex_lock(&priv->wx_mutex);

	snprintf(extra, 45, "PromiscuousMode:%d, FilterSrcSTAFrame:%d",
		 ieee->IntelPromiscuousModeInfo.bPromiscuousOn,
		 ieee->IntelPromiscuousModeInfo.bFilterSourceStationFrame);
	wrqu->data.length = strlen(extra) + 1;

	mutex_unlock(&priv->wx_mutex);

	return 0;
}