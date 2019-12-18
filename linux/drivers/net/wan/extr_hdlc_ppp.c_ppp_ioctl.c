#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ppp {int req_timeout; int cr_retries; int term_retries; int keepalive_interval; int keepalive_timeout; int /*<<< orphan*/  lock; } ;
struct net_device {int flags; int hard_header_len; int /*<<< orphan*/  type; int /*<<< orphan*/ * header_ops; } ;
struct TYPE_4__ {int type; } ;
struct ifreq {TYPE_1__ ifr_settings; } ;
struct hdlc_header {int dummy; } ;
struct TYPE_5__ {int (* attach ) (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * proto; } ;
typedef  TYPE_2__ hdlc_device ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_PPP ; 
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  ENCODING_NRZ ; 
 int EPERM ; 
 int IFF_UP ; 
#define  IF_GET_PROTO 129 
#define  IF_PROTO_PPP 128 
 int /*<<< orphan*/  NETDEV_POST_TYPE_CHANGE ; 
 int /*<<< orphan*/  PARITY_CRC16_PR1_CCITT ; 
 int attach_hdlc_protocol (struct net_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  call_netdevice_notifiers (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 TYPE_2__* dev_to_hdlc (struct net_device*) ; 
 struct ppp* get_ppp (struct net_device*) ; 
 int /*<<< orphan*/  netif_dormant_on (struct net_device*) ; 
 int /*<<< orphan*/  ppp_header_ops ; 
 int /*<<< orphan*/  proto ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ppp_ioctl(struct net_device *dev, struct ifreq *ifr)
{
	hdlc_device *hdlc = dev_to_hdlc(dev);
	struct ppp *ppp;
	int result;

	switch (ifr->ifr_settings.type) {
	case IF_GET_PROTO:
		if (dev_to_hdlc(dev)->proto != &proto)
			return -EINVAL;
		ifr->ifr_settings.type = IF_PROTO_PPP;
		return 0; /* return protocol only, no settable parameters */

	case IF_PROTO_PPP:
		if (!capable(CAP_NET_ADMIN))
			return -EPERM;

		if (dev->flags & IFF_UP)
			return -EBUSY;

		/* no settable parameters */

		result = hdlc->attach(dev, ENCODING_NRZ,PARITY_CRC16_PR1_CCITT);
		if (result)
			return result;

		result = attach_hdlc_protocol(dev, &proto, sizeof(struct ppp));
		if (result)
			return result;

		ppp = get_ppp(dev);
		spin_lock_init(&ppp->lock);
		ppp->req_timeout = 2;
		ppp->cr_retries = 10;
		ppp->term_retries = 2;
		ppp->keepalive_interval = 10;
		ppp->keepalive_timeout = 60;

		dev->hard_header_len = sizeof(struct hdlc_header);
		dev->header_ops = &ppp_header_ops;
		dev->type = ARPHRD_PPP;
		call_netdevice_notifiers(NETDEV_POST_TYPE_CHANGE, dev);
		netif_dormant_on(dev);
		return 0;
	}

	return -EINVAL;
}