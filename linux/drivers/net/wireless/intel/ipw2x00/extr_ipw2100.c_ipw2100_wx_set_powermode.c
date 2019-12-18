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
struct ipw2100_priv {int status; int /*<<< orphan*/  action_mutex; int /*<<< orphan*/  power_mode; } ;

/* Variables and functions */
 int EIO ; 
 int IPW_POWER_AUTO ; 
 int IPW_POWER_LEVEL (int /*<<< orphan*/ ) ; 
 int POWER_MODES ; 
 int STATUS_INITIALIZED ; 
 int ipw2100_set_power_mode (struct ipw2100_priv*,int) ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw2100_wx_set_powermode(struct net_device *dev,
				    struct iw_request_info *info,
				    union iwreq_data *wrqu, char *extra)
{
	struct ipw2100_priv *priv = libipw_priv(dev);
	int err = 0, mode = *(int *)extra;

	mutex_lock(&priv->action_mutex);
	if (!(priv->status & STATUS_INITIALIZED)) {
		err = -EIO;
		goto done;
	}

	if ((mode < 0) || (mode > POWER_MODES))
		mode = IPW_POWER_AUTO;

	if (IPW_POWER_LEVEL(priv->power_mode) != mode)
		err = ipw2100_set_power_mode(priv, mode);
      done:
	mutex_unlock(&priv->action_mutex);
	return err;
}