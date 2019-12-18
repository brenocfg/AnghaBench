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
struct TYPE_2__ {int length; scalar_t__ flags; } ;
union iwreq_data {TYPE_1__ essid; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw2100_priv {int status; int essid_len; int /*<<< orphan*/  action_mutex; int /*<<< orphan*/  essid; int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_STATIC_ESSID ; 
 int EIO ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,...) ; 
 int /*<<< orphan*/  IW_ESSID_MAX_SIZE ; 
 int STATUS_INITIALIZED ; 
 int ipw2100_set_essid (struct ipw2100_priv*,char*,int,int /*<<< orphan*/ ) ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw2100_wx_set_essid(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	struct ipw2100_priv *priv = libipw_priv(dev);
	char *essid = "";	/* ANY */
	int length = 0;
	int err = 0;

	mutex_lock(&priv->action_mutex);
	if (!(priv->status & STATUS_INITIALIZED)) {
		err = -EIO;
		goto done;
	}

	if (wrqu->essid.flags && wrqu->essid.length) {
		length = wrqu->essid.length;
		essid = extra;
	}

	if (length == 0) {
		IPW_DEBUG_WX("Setting ESSID to ANY\n");
		priv->config &= ~CFG_STATIC_ESSID;
		err = ipw2100_set_essid(priv, NULL, 0, 0);
		goto done;
	}

	length = min(length, IW_ESSID_MAX_SIZE);

	priv->config |= CFG_STATIC_ESSID;

	if (priv->essid_len == length && !memcmp(priv->essid, extra, length)) {
		IPW_DEBUG_WX("ESSID set to current ESSID.\n");
		err = 0;
		goto done;
	}

	IPW_DEBUG_WX("Setting ESSID: '%*pE' (%d)\n", length, essid, length);

	priv->essid_len = length;
	memcpy(priv->essid, essid, priv->essid_len);

	err = ipw2100_set_essid(priv, essid, length, 0);

      done:
	mutex_unlock(&priv->action_mutex);
	return err;
}