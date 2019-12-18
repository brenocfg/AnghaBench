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
struct TYPE_3__ {int e; int m; } ;
union iwreq_data {TYPE_1__ freq; } ;
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  channel; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; int /*<<< orphan*/  need_commit; TYPE_2__ reg; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 scalar_t__ SLP_SLEEP ; 
 int /*<<< orphan*/  SME_MODE_SET ; 
 int* frequency_list ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int /*<<< orphan*/ ,int) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_set_freq(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *fwrq, char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);
	int channel;

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;

	/* for SLEEP MODE */
	/* If setting by frequency, convert to a channel */
	if ((fwrq->freq.e == 1) &&
	    (fwrq->freq.m >= 241200000) && (fwrq->freq.m <= 248700000)) {
		int f = fwrq->freq.m / 100000;
		int c = 0;

		while ((c < 14) && (f != frequency_list[c]))
			c++;
		/* Hack to fall through... */
		fwrq->freq.e = 0;
		fwrq->freq.m = c + 1;
	}
	/* Setting by channel number */
	if ((fwrq->freq.m > 1000) || (fwrq->freq.e > 0))
		return -EOPNOTSUPP;

	channel = fwrq->freq.m;
	/* We should do a better check than that,
	 * based on the card capability !!!
	 */
	if ((channel < 1) || (channel > 14)) {
		netdev_dbg(dev, "%s: New channel value of %d is invalid!\n",
			   dev->name, fwrq->freq.m);
		return -EINVAL;
	}

	/* Yes ! We can set it !!! */
	priv->reg.channel = (u8)(channel);
	priv->need_commit |= SME_MODE_SET;

	return -EINPROGRESS;	/* Call commit handler */
}