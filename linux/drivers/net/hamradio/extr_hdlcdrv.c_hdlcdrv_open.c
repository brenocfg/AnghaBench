#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_9__ {scalar_t__ wr; scalar_t__ rd; } ;
struct TYPE_11__ {int tx_state; scalar_t__ calibrate; int /*<<< orphan*/  slotcnt; scalar_t__ ptt; scalar_t__ numbits; scalar_t__ bitbuf; scalar_t__ bitstream; scalar_t__ numflags; scalar_t__ in_hdlc_tx; TYPE_3__ hbuf; } ;
struct TYPE_10__ {int /*<<< orphan*/  slottime; } ;
struct TYPE_7__ {scalar_t__ wr; scalar_t__ rd; } ;
struct TYPE_8__ {scalar_t__ rx_state; scalar_t__ in_hdlc_rx; TYPE_1__ hbuf; } ;
struct hdlcdrv_state {int opened; TYPE_6__* ops; TYPE_5__ hdlctx; TYPE_4__ ch_params; TYPE_2__ hdlcrx; } ;
struct TYPE_12__ {int (* open ) (struct net_device*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 struct hdlcdrv_state* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int stub1 (struct net_device*) ; 

__attribute__((used)) static int hdlcdrv_open(struct net_device *dev)
{
	struct hdlcdrv_state *s = netdev_priv(dev);
	int i;

	if (!s->ops || !s->ops->open)
		return -ENODEV;

	/*
	 * initialise some variables
	 */
	s->opened = 1;
	s->hdlcrx.hbuf.rd = s->hdlcrx.hbuf.wr = 0;
	s->hdlcrx.in_hdlc_rx = 0;
	s->hdlcrx.rx_state = 0;
	
	s->hdlctx.hbuf.rd = s->hdlctx.hbuf.wr = 0;
	s->hdlctx.in_hdlc_tx = 0;
	s->hdlctx.tx_state = 1;
	s->hdlctx.numflags = 0;
	s->hdlctx.bitstream = s->hdlctx.bitbuf = s->hdlctx.numbits = 0;
	s->hdlctx.ptt = 0;
	s->hdlctx.slotcnt = s->ch_params.slottime;
	s->hdlctx.calibrate = 0;

	i = s->ops->open(dev);
	if (i)
		return i;
	netif_start_queue(dev);
	return 0;
}