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
union iwreq_data {scalar_t__ mode; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw2100_priv {int status; int /*<<< orphan*/  action_mutex; TYPE_1__* ieee; } ;
struct TYPE_2__ {scalar_t__ iw_mode; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,scalar_t__) ; 
#define  IW_MODE_ADHOC 131 
#define  IW_MODE_AUTO 130 
#define  IW_MODE_INFRA 129 
#define  IW_MODE_MONITOR 128 
 int STATUS_INITIALIZED ; 
 int ipw2100_switch_mode (struct ipw2100_priv*,int const) ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw2100_wx_set_mode(struct net_device *dev,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{
	struct ipw2100_priv *priv = libipw_priv(dev);
	int err = 0;

	IPW_DEBUG_WX("SET Mode -> %d\n", wrqu->mode);

	if (wrqu->mode == priv->ieee->iw_mode)
		return 0;

	mutex_lock(&priv->action_mutex);
	if (!(priv->status & STATUS_INITIALIZED)) {
		err = -EIO;
		goto done;
	}

	switch (wrqu->mode) {
#ifdef CONFIG_IPW2100_MONITOR
	case IW_MODE_MONITOR:
		err = ipw2100_switch_mode(priv, IW_MODE_MONITOR);
		break;
#endif				/* CONFIG_IPW2100_MONITOR */
	case IW_MODE_ADHOC:
		err = ipw2100_switch_mode(priv, IW_MODE_ADHOC);
		break;
	case IW_MODE_INFRA:
	case IW_MODE_AUTO:
	default:
		err = ipw2100_switch_mode(priv, IW_MODE_INFRA);
		break;
	}

      done:
	mutex_unlock(&priv->action_mutex);
	return err;
}