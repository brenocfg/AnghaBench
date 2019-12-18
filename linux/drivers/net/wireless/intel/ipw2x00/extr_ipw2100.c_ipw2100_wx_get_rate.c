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
typedef  int /*<<< orphan*/  val ;
struct TYPE_2__ {int value; } ;
union iwreq_data {TYPE_1__ bitrate; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw2100_priv {int status; int /*<<< orphan*/  action_mutex; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,...) ; 
 int /*<<< orphan*/  IPW_ORD_CURRENT_TX_RATE ; 
 int STATUS_ASSOCIATED ; 
 int STATUS_ENABLED ; 
 int STATUS_INITIALIZED ; 
 int STATUS_RF_KILL_MASK ; 
#define  TX_RATE_11_MBIT 131 
#define  TX_RATE_1_MBIT 130 
#define  TX_RATE_2_MBIT 129 
#define  TX_RATE_5_5_MBIT 128 
 int TX_RATE_MASK ; 
 int ipw2100_get_ordinal (struct ipw2100_priv*,int /*<<< orphan*/ ,int*,unsigned int*) ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw2100_wx_get_rate(struct net_device *dev,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{
	struct ipw2100_priv *priv = libipw_priv(dev);
	int val;
	unsigned int len = sizeof(val);
	int err = 0;

	if (!(priv->status & STATUS_ENABLED) ||
	    priv->status & STATUS_RF_KILL_MASK ||
	    !(priv->status & STATUS_ASSOCIATED)) {
		wrqu->bitrate.value = 0;
		return 0;
	}

	mutex_lock(&priv->action_mutex);
	if (!(priv->status & STATUS_INITIALIZED)) {
		err = -EIO;
		goto done;
	}

	err = ipw2100_get_ordinal(priv, IPW_ORD_CURRENT_TX_RATE, &val, &len);
	if (err) {
		IPW_DEBUG_WX("failed querying ordinals.\n");
		goto done;
	}

	switch (val & TX_RATE_MASK) {
	case TX_RATE_1_MBIT:
		wrqu->bitrate.value = 1000000;
		break;
	case TX_RATE_2_MBIT:
		wrqu->bitrate.value = 2000000;
		break;
	case TX_RATE_5_5_MBIT:
		wrqu->bitrate.value = 5500000;
		break;
	case TX_RATE_11_MBIT:
		wrqu->bitrate.value = 11000000;
		break;
	default:
		wrqu->bitrate.value = 0;
	}

	IPW_DEBUG_WX("GET Rate -> %d\n", wrqu->bitrate.value);

      done:
	mutex_unlock(&priv->action_mutex);
	return err;
}