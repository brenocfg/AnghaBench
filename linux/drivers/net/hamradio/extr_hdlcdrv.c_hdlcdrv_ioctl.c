#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_3__ stats; int /*<<< orphan*/  dma; int /*<<< orphan*/  irq; int /*<<< orphan*/  base_addr; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct TYPE_27__ {size_t rd; size_t wr; int /*<<< orphan*/ * buffer; } ;
struct TYPE_26__ {size_t rd; size_t wr; int /*<<< orphan*/ * buffer; } ;
struct TYPE_25__ {int bitrate; } ;
struct TYPE_17__ {int slotcnt; int calibrate; } ;
struct TYPE_23__ {int /*<<< orphan*/  dcd; } ;
struct TYPE_20__ {int /*<<< orphan*/  midiiobase; int /*<<< orphan*/  pariobase; int /*<<< orphan*/  seriobase; int /*<<< orphan*/  dma2; } ;
struct TYPE_15__ {int /*<<< orphan*/  fulldup; int /*<<< orphan*/  ppersist; int /*<<< orphan*/  slottime; int /*<<< orphan*/  tx_tail; int /*<<< orphan*/  tx_delay; } ;
struct hdlcdrv_state {TYPE_9__* ops; TYPE_8__ bitbuf_hdlc; TYPE_7__ bitbuf_channel; TYPE_6__ par; TYPE_12__ hdlctx; int /*<<< orphan*/  ptt_keyed; TYPE_4__ hdlcrx; TYPE_1__ ptt_out; TYPE_10__ ch_params; } ;
struct TYPE_24__ {int /*<<< orphan*/  ptt_keyed; int /*<<< orphan*/  dcd; void* ptt; } ;
struct TYPE_21__ {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  ptt_keyed; int /*<<< orphan*/  dcd; void* ptt; } ;
struct TYPE_19__ {int /*<<< orphan*/  midiiobase; int /*<<< orphan*/  pariobase; int /*<<< orphan*/  seriobase; int /*<<< orphan*/  dma2; int /*<<< orphan*/  dma; int /*<<< orphan*/  irq; int /*<<< orphan*/  iobase; } ;
struct TYPE_16__ {int /*<<< orphan*/  fulldup; int /*<<< orphan*/  ppersist; int /*<<< orphan*/  slottime; int /*<<< orphan*/  tx_tail; int /*<<< orphan*/  tx_delay; } ;
struct TYPE_18__ {int calibrate; char* drivername; int /*<<< orphan*/  bits; TYPE_5__ ocs; TYPE_2__ cs; TYPE_14__ mp; TYPE_11__ cp; } ;
struct hdlcdrv_ioctl {int cmd; TYPE_13__ data; } ;
typedef  int /*<<< orphan*/  bi ;
struct TYPE_28__ {int (* ioctl ) (struct net_device*,struct ifreq*,struct hdlcdrv_ioctl*,int) ;int /*<<< orphan*/  drvname; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int EACCES ; 
 int EAGAIN ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOIOCTLCMD ; 
 int EPERM ; 
#define  HDLCDRVCTL_CALIBRATE 137 
#define  HDLCDRVCTL_DRIVERNAME 136 
#define  HDLCDRVCTL_GETBITS 135 
#define  HDLCDRVCTL_GETCHANNELPAR 134 
#define  HDLCDRVCTL_GETMODEMPAR 133 
#define  HDLCDRVCTL_GETSAMPLES 132 
#define  HDLCDRVCTL_GETSTAT 131 
#define  HDLCDRVCTL_OLDGETSTAT 130 
#define  HDLCDRVCTL_SETCHANNELPAR 129 
#define  HDLCDRVCTL_SETMODEMPAR 128 
 int INT_MAX ; 
 int SIOCDEVPRIVATE ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ copy_from_user (struct hdlcdrv_ioctl*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hdlcdrv_ioctl*,int) ; 
 void* hdlcdrv_ptt (struct hdlcdrv_state*) ; 
 struct hdlcdrv_state* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct net_device*,struct ifreq*,struct hdlcdrv_ioctl*,int) ; 
 int stub2 (struct net_device*,struct ifreq*,struct hdlcdrv_ioctl*,int) ; 

__attribute__((used)) static int hdlcdrv_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct hdlcdrv_state *s = netdev_priv(dev);
	struct hdlcdrv_ioctl bi;

	if (cmd != SIOCDEVPRIVATE) {
		if (s->ops && s->ops->ioctl)
			return s->ops->ioctl(dev, ifr, &bi, cmd);
		return -ENOIOCTLCMD;
	}
	if (copy_from_user(&bi, ifr->ifr_data, sizeof(bi)))
		return -EFAULT;

	switch (bi.cmd) {
	default:
		if (s->ops && s->ops->ioctl)
			return s->ops->ioctl(dev, ifr, &bi, cmd);
		return -ENOIOCTLCMD;

	case HDLCDRVCTL_GETCHANNELPAR:
		bi.data.cp.tx_delay = s->ch_params.tx_delay;
		bi.data.cp.tx_tail = s->ch_params.tx_tail;
		bi.data.cp.slottime = s->ch_params.slottime;
		bi.data.cp.ppersist = s->ch_params.ppersist;
		bi.data.cp.fulldup = s->ch_params.fulldup;
		break;

	case HDLCDRVCTL_SETCHANNELPAR:
		if (!capable(CAP_NET_ADMIN))
			return -EACCES;
		s->ch_params.tx_delay = bi.data.cp.tx_delay;
		s->ch_params.tx_tail = bi.data.cp.tx_tail;
		s->ch_params.slottime = bi.data.cp.slottime;
		s->ch_params.ppersist = bi.data.cp.ppersist;
		s->ch_params.fulldup = bi.data.cp.fulldup;
		s->hdlctx.slotcnt = 1;
		return 0;
		
	case HDLCDRVCTL_GETMODEMPAR:
		bi.data.mp.iobase = dev->base_addr;
		bi.data.mp.irq = dev->irq;
		bi.data.mp.dma = dev->dma;
		bi.data.mp.dma2 = s->ptt_out.dma2;
		bi.data.mp.seriobase = s->ptt_out.seriobase;
		bi.data.mp.pariobase = s->ptt_out.pariobase;
		bi.data.mp.midiiobase = s->ptt_out.midiiobase;
		break;

	case HDLCDRVCTL_SETMODEMPAR:
		if ((!capable(CAP_SYS_RAWIO)) || netif_running(dev))
			return -EACCES;
		dev->base_addr = bi.data.mp.iobase;
		dev->irq = bi.data.mp.irq;
		dev->dma = bi.data.mp.dma;
		s->ptt_out.dma2 = bi.data.mp.dma2;
		s->ptt_out.seriobase = bi.data.mp.seriobase;
		s->ptt_out.pariobase = bi.data.mp.pariobase;
		s->ptt_out.midiiobase = bi.data.mp.midiiobase;
		return 0;	
	
	case HDLCDRVCTL_GETSTAT:
		bi.data.cs.ptt = hdlcdrv_ptt(s);
		bi.data.cs.dcd = s->hdlcrx.dcd;
		bi.data.cs.ptt_keyed = s->ptt_keyed;
		bi.data.cs.tx_packets = dev->stats.tx_packets;
		bi.data.cs.tx_errors = dev->stats.tx_errors;
		bi.data.cs.rx_packets = dev->stats.rx_packets;
		bi.data.cs.rx_errors = dev->stats.rx_errors;
		break;		

	case HDLCDRVCTL_OLDGETSTAT:
		bi.data.ocs.ptt = hdlcdrv_ptt(s);
		bi.data.ocs.dcd = s->hdlcrx.dcd;
		bi.data.ocs.ptt_keyed = s->ptt_keyed;
		break;		

	case HDLCDRVCTL_CALIBRATE:
		if(!capable(CAP_SYS_RAWIO))
			return -EPERM;
		if (s->par.bitrate <= 0)
			return -EINVAL;
		if (bi.data.calibrate > INT_MAX / s->par.bitrate)
			return -EINVAL;
		s->hdlctx.calibrate = bi.data.calibrate * s->par.bitrate / 16;
		return 0;

	case HDLCDRVCTL_GETSAMPLES:
#ifndef HDLCDRV_DEBUG
		return -EPERM;
#else /* HDLCDRV_DEBUG */
		if (s->bitbuf_channel.rd == s->bitbuf_channel.wr) 
			return -EAGAIN;
		bi.data.bits = 
			s->bitbuf_channel.buffer[s->bitbuf_channel.rd];
		s->bitbuf_channel.rd = (s->bitbuf_channel.rd+1) %
			sizeof(s->bitbuf_channel.buffer);
		break;
#endif /* HDLCDRV_DEBUG */
				
	case HDLCDRVCTL_GETBITS:
#ifndef HDLCDRV_DEBUG
		return -EPERM;
#else /* HDLCDRV_DEBUG */
		if (s->bitbuf_hdlc.rd == s->bitbuf_hdlc.wr) 
			return -EAGAIN;
		bi.data.bits = 
			s->bitbuf_hdlc.buffer[s->bitbuf_hdlc.rd];
		s->bitbuf_hdlc.rd = (s->bitbuf_hdlc.rd+1) %
			sizeof(s->bitbuf_hdlc.buffer);
		break;		
#endif /* HDLCDRV_DEBUG */

	case HDLCDRVCTL_DRIVERNAME:
		if (s->ops && s->ops->drvname) {
			strncpy(bi.data.drivername, s->ops->drvname, 
				sizeof(bi.data.drivername));
			break;
		}
		bi.data.drivername[0] = '\0';
		break;
		
	}
	if (copy_to_user(ifr->ifr_data, &bi, sizeof(bi)))
		return -EFAULT;
	return 0;

}