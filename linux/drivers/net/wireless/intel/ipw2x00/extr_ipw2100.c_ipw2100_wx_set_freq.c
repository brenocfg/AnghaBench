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
struct iw_freq {int e; int m; } ;
union iwreq_data {struct iw_freq freq; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw2100_priv {int status; int /*<<< orphan*/  action_mutex; TYPE_1__* ieee; } ;
struct TYPE_2__ {scalar_t__ iw_mode; } ;

/* Variables and functions */
 int EIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,int) ; 
 scalar_t__ IW_MODE_INFRA ; 
 int REG_MAX_CHANNEL ; 
 int STATUS_INITIALIZED ; 
 int* ipw2100_frequencies ; 
 int ipw2100_set_channel (struct ipw2100_priv*,int,int /*<<< orphan*/ ) ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw2100_wx_set_freq(struct net_device *dev,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{
	struct ipw2100_priv *priv = libipw_priv(dev);
	struct iw_freq *fwrq = &wrqu->freq;
	int err = 0;

	if (priv->ieee->iw_mode == IW_MODE_INFRA)
		return -EOPNOTSUPP;

	mutex_lock(&priv->action_mutex);
	if (!(priv->status & STATUS_INITIALIZED)) {
		err = -EIO;
		goto done;
	}

	/* if setting by freq convert to channel */
	if (fwrq->e == 1) {
		if ((fwrq->m >= (int)2.412e8 && fwrq->m <= (int)2.487e8)) {
			int f = fwrq->m / 100000;
			int c = 0;

			while ((c < REG_MAX_CHANNEL) &&
			       (f != ipw2100_frequencies[c]))
				c++;

			/* hack to fall through */
			fwrq->e = 0;
			fwrq->m = c + 1;
		}
	}

	if (fwrq->e > 0 || fwrq->m > 1000) {
		err = -EOPNOTSUPP;
		goto done;
	} else {		/* Set the channel */
		IPW_DEBUG_WX("SET Freq/Channel -> %d\n", fwrq->m);
		err = ipw2100_set_channel(priv, fwrq->m, 0);
	}

      done:
	mutex_unlock(&priv->action_mutex);
	return err;
}