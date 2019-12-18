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
struct ipw_priv {int config; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int CFG_PREAMBLE_LONG ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPW_DEBUG_ASSOC (char*) ; 
 int /*<<< orphan*/  ipw_associate (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_disassociate (struct ipw_priv*) ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw_wx_set_preamble(struct net_device *dev,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);
	int mode = *(int *)extra;
	mutex_lock(&priv->mutex);
	/* Switching from SHORT -> LONG requires a disassociation */
	if (mode == 1) {
		if (!(priv->config & CFG_PREAMBLE_LONG)) {
			priv->config |= CFG_PREAMBLE_LONG;

			/* Network configuration changed -- force [re]association */
			IPW_DEBUG_ASSOC
			    ("[re]association triggered due to preamble change.\n");
			if (!ipw_disassociate(priv))
				ipw_associate(priv);
		}
		goto done;
	}

	if (mode == 0) {
		priv->config &= ~CFG_PREAMBLE_LONG;
		goto done;
	}
	mutex_unlock(&priv->mutex);
	return -EINVAL;

      done:
	mutex_unlock(&priv->mutex);
	return 0;
}