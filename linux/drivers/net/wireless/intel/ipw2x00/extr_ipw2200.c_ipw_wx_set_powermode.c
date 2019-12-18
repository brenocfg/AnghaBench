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
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw_priv {int power_mode; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_WX (char*) ; 
 int IPW_POWER_AC ; 
 int IPW_POWER_ENABLED ; 
 int IPW_POWER_LEVEL (int) ; 
 int IPW_POWER_LIMIT ; 
 int ipw_send_power_mode (struct ipw_priv*,int) ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw_wx_set_powermode(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);
	int mode = *(int *)extra;
	int err;

	mutex_lock(&priv->mutex);
	if ((mode < 1) || (mode > IPW_POWER_LIMIT))
		mode = IPW_POWER_AC;

	if (IPW_POWER_LEVEL(priv->power_mode) != mode) {
		err = ipw_send_power_mode(priv, mode);
		if (err) {
			IPW_DEBUG_WX("failed setting power mode.\n");
			mutex_unlock(&priv->mutex);
			return err;
		}
		priv->power_mode = IPW_POWER_ENABLED | mode;
	}
	mutex_unlock(&priv->mutex);
	return 0;
}