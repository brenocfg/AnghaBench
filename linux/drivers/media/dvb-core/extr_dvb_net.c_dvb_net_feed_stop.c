#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; } ;
struct dvb_net_priv {scalar_t__ feedtype; int multi_num; int /*<<< orphan*/  mutex; TYPE_2__* tsfeed; TYPE_1__* demux; TYPE_5__* secfeed; int /*<<< orphan*/ ** multi_secfilter; int /*<<< orphan*/ * secfilter; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* release_filter ) (TYPE_5__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* stop_filtering ) (TYPE_5__*) ;scalar_t__ is_filtering; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* stop_filtering ) (TYPE_2__*) ;scalar_t__ is_filtering; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* release_ts_feed ) (TYPE_1__*,TYPE_2__*) ;int /*<<< orphan*/  (* release_section_feed ) (TYPE_1__*,TYPE_5__*) ;} ;

/* Variables and functions */
 scalar_t__ DVB_NET_FEEDTYPE_MPE ; 
 scalar_t__ DVB_NET_FEEDTYPE_ULE ; 
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 struct dvb_net_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,TYPE_5__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int dvb_net_feed_stop(struct net_device *dev)
{
	struct dvb_net_priv *priv = netdev_priv(dev);
	int i, ret = 0;

	mutex_lock(&priv->mutex);
	if (priv->feedtype == DVB_NET_FEEDTYPE_MPE) {
		if (priv->secfeed) {
			if (priv->secfeed->is_filtering) {
				netdev_dbg(dev, "stop secfeed\n");
				priv->secfeed->stop_filtering(priv->secfeed);
			}

			if (priv->secfilter) {
				netdev_dbg(dev, "release secfilter\n");
				priv->secfeed->release_filter(priv->secfeed,
							      priv->secfilter);
				priv->secfilter=NULL;
			}

			for (i=0; i<priv->multi_num; i++) {
				if (priv->multi_secfilter[i]) {
					netdev_dbg(dev, "release multi_filter[%d]\n",
						   i);
					priv->secfeed->release_filter(priv->secfeed,
								      priv->multi_secfilter[i]);
					priv->multi_secfilter[i] = NULL;
				}
			}

			priv->demux->release_section_feed(priv->demux, priv->secfeed);
			priv->secfeed = NULL;
		} else
			pr_err("%s: no feed to stop\n", dev->name);
	} else if (priv->feedtype == DVB_NET_FEEDTYPE_ULE) {
		if (priv->tsfeed) {
			if (priv->tsfeed->is_filtering) {
				netdev_dbg(dev, "stop tsfeed\n");
				priv->tsfeed->stop_filtering(priv->tsfeed);
			}
			priv->demux->release_ts_feed(priv->demux, priv->tsfeed);
			priv->tsfeed = NULL;
		}
		else
			pr_err("%s: no ts feed to stop\n", dev->name);
	} else
		ret = -EINVAL;
	mutex_unlock(&priv->mutex);
	return ret;
}