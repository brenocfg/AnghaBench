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
typedef  int u32 ;
struct sched_class {void* idx; } ;
struct port_info {int nqsets; int /*<<< orphan*/  tx_chan; int /*<<< orphan*/  port_id; struct adapter* adapter; } ;
struct net_device {int /*<<< orphan*/  mtu; } ;
struct TYPE_3__ {int maxrate; int /*<<< orphan*/  pktsize; scalar_t__ weight; scalar_t__ minrate; void* class; int /*<<< orphan*/  channel; int /*<<< orphan*/  ratemode; int /*<<< orphan*/  rateunit; int /*<<< orphan*/  mode; int /*<<< orphan*/  level; } ;
struct TYPE_4__ {TYPE_1__ params; } ;
struct ch_sched_queue {int queue; void* class; TYPE_2__ u; int /*<<< orphan*/  type; } ;
struct ch_sched_params {int queue; void* class; TYPE_2__ u; int /*<<< orphan*/  type; } ;
struct adapter {int flags; int /*<<< orphan*/  pdev_dev; } ;
typedef  int /*<<< orphan*/  qe ;
typedef  int /*<<< orphan*/  p ;

/* Variables and functions */
 int CXGB4_FULL_INIT_DONE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int ERANGE ; 
 int /*<<< orphan*/  SCHED_CLASS_LEVEL_CL_RL ; 
 int /*<<< orphan*/  SCHED_CLASS_MODE_CLASS ; 
 int /*<<< orphan*/  SCHED_CLASS_RATEMODE_ABS ; 
 int /*<<< orphan*/  SCHED_CLASS_RATEUNIT_BITS ; 
 int /*<<< orphan*/  SCHED_CLASS_TYPE_PACKET ; 
 void* SCHED_CLS_NONE ; 
 int SCHED_MAX_RATE_KBPS ; 
 int /*<<< orphan*/  SCHED_QUEUE ; 
 int /*<<< orphan*/  can_sched (struct net_device*) ; 
 struct sched_class* cxgb4_sched_class_alloc (struct net_device*,struct ch_sched_queue*) ; 
 int cxgb4_sched_class_bind (struct net_device*,void*,int /*<<< orphan*/ ) ; 
 int cxgb4_sched_class_unbind (struct net_device*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  memset (struct ch_sched_queue*,int /*<<< orphan*/ ,int) ; 
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int cxgb_set_tx_maxrate(struct net_device *dev, int index, u32 rate)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adap = pi->adapter;
	struct sched_class *e;
	struct ch_sched_params p;
	struct ch_sched_queue qe;
	u32 req_rate;
	int err = 0;

	if (!can_sched(dev))
		return -ENOTSUPP;

	if (index < 0 || index > pi->nqsets - 1)
		return -EINVAL;

	if (!(adap->flags & CXGB4_FULL_INIT_DONE)) {
		dev_err(adap->pdev_dev,
			"Failed to rate limit on queue %d. Link Down?\n",
			index);
		return -EINVAL;
	}

	/* Convert from Mbps to Kbps */
	req_rate = rate * 1000;

	/* Max rate is 100 Gbps */
	if (req_rate > SCHED_MAX_RATE_KBPS) {
		dev_err(adap->pdev_dev,
			"Invalid rate %u Mbps, Max rate is %u Mbps\n",
			rate, SCHED_MAX_RATE_KBPS / 1000);
		return -ERANGE;
	}

	/* First unbind the queue from any existing class */
	memset(&qe, 0, sizeof(qe));
	qe.queue = index;
	qe.class = SCHED_CLS_NONE;

	err = cxgb4_sched_class_unbind(dev, (void *)(&qe), SCHED_QUEUE);
	if (err) {
		dev_err(adap->pdev_dev,
			"Unbinding Queue %d on port %d fail. Err: %d\n",
			index, pi->port_id, err);
		return err;
	}

	/* Queue already unbound */
	if (!req_rate)
		return 0;

	/* Fetch any available unused or matching scheduling class */
	memset(&p, 0, sizeof(p));
	p.type = SCHED_CLASS_TYPE_PACKET;
	p.u.params.level    = SCHED_CLASS_LEVEL_CL_RL;
	p.u.params.mode     = SCHED_CLASS_MODE_CLASS;
	p.u.params.rateunit = SCHED_CLASS_RATEUNIT_BITS;
	p.u.params.ratemode = SCHED_CLASS_RATEMODE_ABS;
	p.u.params.channel  = pi->tx_chan;
	p.u.params.class    = SCHED_CLS_NONE;
	p.u.params.minrate  = 0;
	p.u.params.maxrate  = req_rate;
	p.u.params.weight   = 0;
	p.u.params.pktsize  = dev->mtu;

	e = cxgb4_sched_class_alloc(dev, &p);
	if (!e)
		return -ENOMEM;

	/* Bind the queue to a scheduling class */
	memset(&qe, 0, sizeof(qe));
	qe.queue = index;
	qe.class = e->idx;

	err = cxgb4_sched_class_bind(dev, (void *)(&qe), SCHED_QUEUE);
	if (err)
		dev_err(adap->pdev_dev,
			"Queue rate limiting failed. Err: %d\n", err);
	return err;
}