#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_7__ stats; int /*<<< orphan*/  dma; int /*<<< orphan*/  irq; int /*<<< orphan*/  base_addr; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct TYPE_17__ {int ptt; int dcd; int /*<<< orphan*/  ptt_keyed; } ;
struct TYPE_15__ {int ptt; int dcd; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  ptt_keyed; } ;
struct TYPE_14__ {int /*<<< orphan*/  iobase; int /*<<< orphan*/  midiiobase; int /*<<< orphan*/  pariobase; int /*<<< orphan*/  seriobase; int /*<<< orphan*/  dma2; int /*<<< orphan*/  dma; int /*<<< orphan*/  irq; } ;
struct TYPE_12__ {int /*<<< orphan*/  fulldup; int /*<<< orphan*/  ppersist; int /*<<< orphan*/  slottime; int /*<<< orphan*/  tx_tail; int /*<<< orphan*/  tx_delay; } ;
struct TYPE_18__ {int calibrate; char* drivername; char* modename; TYPE_8__ ocs; TYPE_6__ cs; TYPE_5__ mp; TYPE_3__ cp; } ;
struct hdlcdrv_ioctl {int cmd; TYPE_9__ data; } ;
struct TYPE_10__ {int fclk; int bps; int /*<<< orphan*/  extmodem; int /*<<< orphan*/  intclk; int /*<<< orphan*/  loopback; } ;
struct TYPE_13__ {int slotcnt; int calibrate; } ;
struct TYPE_11__ {int /*<<< orphan*/  fulldup; int /*<<< orphan*/  ppersist; int /*<<< orphan*/  slottime; int /*<<< orphan*/  tx_tail; int /*<<< orphan*/  tx_delay; } ;
struct baycom_state {int stat; int bitrate; TYPE_1__ cfg; TYPE_4__ hdlctx; int /*<<< orphan*/  ptt_keyed; TYPE_2__ ch_params; } ;
typedef  int /*<<< orphan*/  hi ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int EACCES ; 
 int EFAULT ; 
 int ENOIOCTLCMD ; 
 int EPP_DCDBIT ; 
 int EPP_PTTBIT ; 
#define  HDLCDRVCTL_CALIBRATE 139 
#define  HDLCDRVCTL_DRIVERNAME 138 
#define  HDLCDRVCTL_GETCHANNELPAR 137 
#define  HDLCDRVCTL_GETMODE 136 
#define  HDLCDRVCTL_GETMODEMPAR 135 
#define  HDLCDRVCTL_GETSTAT 134 
#define  HDLCDRVCTL_MODELIST 133 
#define  HDLCDRVCTL_MODEMPARMASK 132 
#define  HDLCDRVCTL_OLDGETSTAT 131 
#define  HDLCDRVCTL_SETCHANNELPAR 130 
#define  HDLCDRVCTL_SETMODE 129 
#define  HDLCDRVCTL_SETMODEMPAR 128 
 int HDLCDRV_PARMASK_IOBASE ; 
 int SIOCDEVPRIVATE ; 
 int baycom_setmode (struct baycom_state*,char*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ copy_from_user (struct hdlcdrv_ioctl*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hdlcdrv_ioctl*,int) ; 
 struct baycom_state* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,int,int,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static int baycom_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct baycom_state *bc = netdev_priv(dev);
	struct hdlcdrv_ioctl hi;

	if (cmd != SIOCDEVPRIVATE)
		return -ENOIOCTLCMD;

	if (copy_from_user(&hi, ifr->ifr_data, sizeof(hi)))
		return -EFAULT;
	switch (hi.cmd) {
	default:
		return -ENOIOCTLCMD;

	case HDLCDRVCTL_GETCHANNELPAR:
		hi.data.cp.tx_delay = bc->ch_params.tx_delay;
		hi.data.cp.tx_tail = bc->ch_params.tx_tail;
		hi.data.cp.slottime = bc->ch_params.slottime;
		hi.data.cp.ppersist = bc->ch_params.ppersist;
		hi.data.cp.fulldup = bc->ch_params.fulldup;
		break;

	case HDLCDRVCTL_SETCHANNELPAR:
		if (!capable(CAP_NET_ADMIN))
			return -EACCES;
		bc->ch_params.tx_delay = hi.data.cp.tx_delay;
		bc->ch_params.tx_tail = hi.data.cp.tx_tail;
		bc->ch_params.slottime = hi.data.cp.slottime;
		bc->ch_params.ppersist = hi.data.cp.ppersist;
		bc->ch_params.fulldup = hi.data.cp.fulldup;
		bc->hdlctx.slotcnt = 1;
		return 0;
		
	case HDLCDRVCTL_GETMODEMPAR:
		hi.data.mp.iobase = dev->base_addr;
		hi.data.mp.irq = dev->irq;
		hi.data.mp.dma = dev->dma;
		hi.data.mp.dma2 = 0;
		hi.data.mp.seriobase = 0;
		hi.data.mp.pariobase = 0;
		hi.data.mp.midiiobase = 0;
		break;

	case HDLCDRVCTL_SETMODEMPAR:
		if ((!capable(CAP_SYS_RAWIO)) || netif_running(dev))
			return -EACCES;
		dev->base_addr = hi.data.mp.iobase;
		dev->irq = /*hi.data.mp.irq*/0;
		dev->dma = /*hi.data.mp.dma*/0;
		return 0;	
		
	case HDLCDRVCTL_GETSTAT:
		hi.data.cs.ptt = !!(bc->stat & EPP_PTTBIT);
		hi.data.cs.dcd = !(bc->stat & EPP_DCDBIT);
		hi.data.cs.ptt_keyed = bc->ptt_keyed;
		hi.data.cs.tx_packets = dev->stats.tx_packets;
		hi.data.cs.tx_errors = dev->stats.tx_errors;
		hi.data.cs.rx_packets = dev->stats.rx_packets;
		hi.data.cs.rx_errors = dev->stats.rx_errors;
		break;		

	case HDLCDRVCTL_OLDGETSTAT:
		hi.data.ocs.ptt = !!(bc->stat & EPP_PTTBIT);
		hi.data.ocs.dcd = !(bc->stat & EPP_DCDBIT);
		hi.data.ocs.ptt_keyed = bc->ptt_keyed;
		break;		

	case HDLCDRVCTL_CALIBRATE:
		if (!capable(CAP_SYS_RAWIO))
			return -EACCES;
		bc->hdlctx.calibrate = hi.data.calibrate * bc->bitrate / 8;
		return 0;

	case HDLCDRVCTL_DRIVERNAME:
		strncpy(hi.data.drivername, "baycom_epp", sizeof(hi.data.drivername));
		break;
		
	case HDLCDRVCTL_GETMODE:
		sprintf(hi.data.modename, "%sclk,%smodem,fclk=%d,bps=%d%s", 
			bc->cfg.intclk ? "int" : "ext",
			bc->cfg.extmodem ? "ext" : "int", bc->cfg.fclk, bc->cfg.bps,
			bc->cfg.loopback ? ",loopback" : "");
		break;

	case HDLCDRVCTL_SETMODE:
		if (!capable(CAP_NET_ADMIN) || netif_running(dev))
			return -EACCES;
		hi.data.modename[sizeof(hi.data.modename)-1] = '\0';
		return baycom_setmode(bc, hi.data.modename);

	case HDLCDRVCTL_MODELIST:
		strncpy(hi.data.modename, "intclk,extclk,intmodem,extmodem,divider=x",
			sizeof(hi.data.modename));
		break;

	case HDLCDRVCTL_MODEMPARMASK:
		return HDLCDRV_PARMASK_IOBASE;

	}
	if (copy_to_user(ifr->ifr_data, &hi, sizeof(hi)))
		return -EFAULT;
	return 0;
}