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
typedef  void* u8 ;
struct net_device {int /*<<< orphan*/  name; } ;
struct dvb_net_priv {TYPE_1__* secfeed; } ;
struct dmx_section_filter {int* filter_value; int* filter_mask; int* filter_mode; void* priv; } ;
struct TYPE_2__ {int (* allocate_filter ) (TYPE_1__*,struct dmx_section_filter**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMX_MAX_FILTER_SIZE ; 
 int /*<<< orphan*/  memset (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,void**,void**) ; 
 struct dvb_net_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,struct dmx_section_filter**) ; 

__attribute__((used)) static int dvb_net_filter_sec_set(struct net_device *dev,
		   struct dmx_section_filter **secfilter,
		   u8 *mac, u8 *mac_mask)
{
	struct dvb_net_priv *priv = netdev_priv(dev);
	int ret;

	*secfilter=NULL;
	ret = priv->secfeed->allocate_filter(priv->secfeed, secfilter);
	if (ret<0) {
		pr_err("%s: could not get filter\n", dev->name);
		return ret;
	}

	(*secfilter)->priv=(void *) dev;

	memset((*secfilter)->filter_value, 0x00, DMX_MAX_FILTER_SIZE);
	memset((*secfilter)->filter_mask,  0x00, DMX_MAX_FILTER_SIZE);
	memset((*secfilter)->filter_mode,  0xff, DMX_MAX_FILTER_SIZE);

	(*secfilter)->filter_value[0]=0x3e;
	(*secfilter)->filter_value[3]=mac[5];
	(*secfilter)->filter_value[4]=mac[4];
	(*secfilter)->filter_value[8]=mac[3];
	(*secfilter)->filter_value[9]=mac[2];
	(*secfilter)->filter_value[10]=mac[1];
	(*secfilter)->filter_value[11]=mac[0];

	(*secfilter)->filter_mask[0] = 0xff;
	(*secfilter)->filter_mask[3] = mac_mask[5];
	(*secfilter)->filter_mask[4] = mac_mask[4];
	(*secfilter)->filter_mask[8] = mac_mask[3];
	(*secfilter)->filter_mask[9] = mac_mask[2];
	(*secfilter)->filter_mask[10] = mac_mask[1];
	(*secfilter)->filter_mask[11]=mac_mask[0];

	netdev_dbg(dev, "filter mac=%pM mask=%pM\n", mac, mac_mask);

	return 0;
}