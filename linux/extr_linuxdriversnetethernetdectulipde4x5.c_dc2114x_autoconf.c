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
typedef  int /*<<< orphan*/  u_long ;
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct TYPE_4__ {int autosense; } ;
struct de4x5_private {int media; int timeout; int tx_enable; int autosense; int infoblock_media; int fdx; size_t active; int local_state; int tmp; int /*<<< orphan*/  tcount; int /*<<< orphan*/  useSROM; int /*<<< orphan*/  linkOK; TYPE_1__* phy; TYPE_2__ params; } ;
typedef  int s32 ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
#define  ANS 136 
#define  AUI 135 
#define  AUI_SUSPECT 134 
 int AUTO ; 
#define  BNC 133 
#define  BNC_SUSPECT 132 
 int DE4X5_AUTOSENSE_MS ; 
 int /*<<< orphan*/  DE4X5_MII ; 
 int /*<<< orphan*/  DE4X5_OMR ; 
 int /*<<< orphan*/  DE4X5_SISR ; 
 int /*<<< orphan*/  DISABLE_IRQs ; 
#define  INIT 131 
 int /*<<< orphan*/  MII_ANA ; 
 int MII_ANA_100M ; 
 int MII_ANA_10M ; 
 int MII_ANA_CSMA ; 
 int MII_ANA_FDAM ; 
 int MII_ANA_TAF ; 
 int /*<<< orphan*/  MII_ANLPA ; 
 int MII_ANLPA_RF ; 
 int MII_ANLPA_TAF ; 
 int /*<<< orphan*/  MII_CR ; 
 int MII_CR_ASSE ; 
 int MII_CR_RAN ; 
 int /*<<< orphan*/  MII_SR ; 
 int MII_SR_ANC ; 
 int MII_SR_ASSC ; 
 int OMR_FDX ; 
 int PDET_LINK_WAIT ; 
 int /*<<< orphan*/  SET_100Mb ; 
 int /*<<< orphan*/  SET_10Mb ; 
 int SISR_SRA ; 
#define  SPD_DET 130 
 int TIMER_CB ; 
 int TP ; 
#define  _100Mb 129 
#define  _10Mb 128 
 int /*<<< orphan*/  de4x5_init_connection (struct net_device*) ; 
 int de4x5_reset_phy (struct net_device*) ; 
 int /*<<< orphan*/  de4x5_save_skbs (struct net_device*) ; 
 int de4x5_suspect_state (struct net_device*,int,int const,int (*) (struct net_device*,int),int (*) (struct net_device*)) ; 
 int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_100_up (struct net_device*) ; 
 int /*<<< orphan*/  is_10_up (struct net_device*) ; 
 int is_anc_capable (struct net_device*) ; 
 int /*<<< orphan*/  is_spd_100 (struct net_device*) ; 
 int mii_rd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_wr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 
 int ping_media (struct net_device*,int) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  srom_map_media (struct net_device*) ; 
 int test_for_100Mb (struct net_device*,int) ; 
 int test_media (struct net_device*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int test_mii_reg (struct net_device*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  wait_for_link (struct net_device*) ; 

__attribute__((used)) static int
dc2114x_autoconf(struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_long iobase = dev->base_addr;
    s32 cr, anlpa, ana, cap, irqs, irq_mask, imr, omr, slnk, sr, sts;
    int next_tick = DE4X5_AUTOSENSE_MS;

    switch (lp->media) {
    case INIT:
        if (lp->timeout < 0) {
	    DISABLE_IRQs;
	    lp->tx_enable = false;
	    lp->linkOK = 0;
            lp->timeout = -1;
	    de4x5_save_skbs(dev);            /* Save non transmitted skb's */
	    if (lp->params.autosense & ~AUTO) {
		srom_map_media(dev);         /* Fixed media requested      */
		if (lp->media != lp->params.autosense) {
		    lp->tcount++;
		    lp->media = INIT;
		    return next_tick;
		}
		lp->media = INIT;
	    }
	}
	if ((next_tick = de4x5_reset_phy(dev)) < 0) {
	    next_tick &= ~TIMER_CB;
	} else {
	    if (lp->autosense == _100Mb) {
		lp->media = _100Mb;
	    } else if (lp->autosense == _10Mb) {
		lp->media = _10Mb;
	    } else if (lp->autosense == TP) {
		lp->media = TP;
	    } else if (lp->autosense == BNC) {
		lp->media = BNC;
	    } else if (lp->autosense == AUI) {
		lp->media = AUI;
	    } else {
		lp->media = SPD_DET;
		if ((lp->infoblock_media == ANS) &&
		                    ((sr=is_anc_capable(dev)) & MII_SR_ANC)) {
		    ana = (((sr >> 6) & MII_ANA_TAF) | MII_ANA_CSMA);
		    ana &= (lp->fdx ? ~0 : ~MII_ANA_FDAM);
		    mii_wr(ana, MII_ANA, lp->phy[lp->active].addr, DE4X5_MII);
		    lp->media = ANS;
		}
	    }
	    lp->local_state = 0;
	    next_tick = dc2114x_autoconf(dev);
        }
	break;

    case ANS:
	switch (lp->local_state) {
	case 0:
	    if (lp->timeout < 0) {
		mii_wr(MII_CR_ASSE | MII_CR_RAN, MII_CR, lp->phy[lp->active].addr, DE4X5_MII);
	    }
	    cr = test_mii_reg(dev, MII_CR, MII_CR_RAN, false, 500);
	    if (cr < 0) {
		next_tick = cr & ~TIMER_CB;
	    } else {
		if (cr) {
		    lp->local_state = 0;
		    lp->media = SPD_DET;
		} else {
		    lp->local_state++;
		}
		next_tick = dc2114x_autoconf(dev);
	    }
	    break;

	case 1:
	    sr = test_mii_reg(dev, MII_SR, MII_SR_ASSC, true, 2000);
	    if (sr < 0) {
		next_tick = sr & ~TIMER_CB;
	    } else {
		lp->media = SPD_DET;
		lp->local_state = 0;
		if (sr) {                         /* Success! */
		    lp->tmp = MII_SR_ASSC;
		    anlpa = mii_rd(MII_ANLPA, lp->phy[lp->active].addr, DE4X5_MII);
		    ana = mii_rd(MII_ANA, lp->phy[lp->active].addr, DE4X5_MII);
		    if (!(anlpa & MII_ANLPA_RF) &&
			 (cap = anlpa & MII_ANLPA_TAF & ana)) {
			if (cap & MII_ANA_100M) {
			    lp->fdx = (ana & anlpa & MII_ANA_FDAM & MII_ANA_100M) != 0;
			    lp->media = _100Mb;
			} else if (cap & MII_ANA_10M) {
			    lp->fdx = (ana & anlpa & MII_ANA_FDAM & MII_ANA_10M) != 0;
			    lp->media = _10Mb;
			}
		    }
		}                       /* Auto Negotiation failed to finish */
		next_tick = dc2114x_autoconf(dev);
	    }                           /* Auto Negotiation failed to start  */
	    break;
	}
	break;

    case AUI:
	if (!lp->tx_enable) {
	    if (lp->timeout < 0) {
		omr = inl(DE4X5_OMR);   /* Set up half duplex for AUI        */
		outl(omr & ~OMR_FDX, DE4X5_OMR);
	    }
	    irqs = 0;
	    irq_mask = 0;
	    sts = test_media(dev,irqs, irq_mask, 0, 0, 0, 1000);
	    if (sts < 0) {
		next_tick = sts & ~TIMER_CB;
	    } else {
		if (!(inl(DE4X5_SISR) & SISR_SRA) && (lp->autosense == AUTO)) {
		    lp->media = BNC;
		    next_tick = dc2114x_autoconf(dev);
		} else {
		    lp->local_state = 1;
		    de4x5_init_connection(dev);
		}
	    }
	} else if (!lp->linkOK && (lp->autosense == AUTO)) {
	    lp->media = AUI_SUSPECT;
	    next_tick = 3000;
	}
	break;

    case AUI_SUSPECT:
	next_tick = de4x5_suspect_state(dev, 1000, AUI, ping_media, dc2114x_autoconf);
	break;

    case BNC:
	switch (lp->local_state) {
	case 0:
	    if (lp->timeout < 0) {
		omr = inl(DE4X5_OMR);          /* Set up half duplex for BNC */
		outl(omr & ~OMR_FDX, DE4X5_OMR);
	    }
	    irqs = 0;
	    irq_mask = 0;
	    sts = test_media(dev,irqs, irq_mask, 0, 0, 0, 1000);
	    if (sts < 0) {
		next_tick = sts & ~TIMER_CB;
	    } else {
		lp->local_state++;             /* Ensure media connected */
		next_tick = dc2114x_autoconf(dev);
	    }
	    break;

	case 1:
	    if (!lp->tx_enable) {
		if ((sts = ping_media(dev, 3000)) < 0) {
		    next_tick = sts & ~TIMER_CB;
		} else {
		    if (sts) {
			lp->local_state = 0;
			lp->tcount++;
			lp->media = INIT;
		    } else {
			de4x5_init_connection(dev);
		    }
		}
	    } else if (!lp->linkOK && (lp->autosense == AUTO)) {
		lp->media = BNC_SUSPECT;
		next_tick = 3000;
	    }
	    break;
	}
	break;

    case BNC_SUSPECT:
	next_tick = de4x5_suspect_state(dev, 1000, BNC, ping_media, dc2114x_autoconf);
	break;

    case SPD_DET:                              /* Choose 10Mb/s or 100Mb/s */
	  if (srom_map_media(dev) < 0) {
	      lp->tcount++;
	      lp->media = INIT;
	      return next_tick;
	  }
	  if (lp->media == _100Mb) {
	      if ((slnk = test_for_100Mb(dev, 6500)) < 0) {
		  lp->media = SPD_DET;
		  return slnk & ~TIMER_CB;
	      }
	  } else {
	      if (wait_for_link(dev) < 0) {
		  lp->media = SPD_DET;
		  return PDET_LINK_WAIT;
	      }
	  }
	  if (lp->media == ANS) {           /* Do MII parallel detection */
	      if (is_spd_100(dev)) {
		  lp->media = _100Mb;
	      } else {
		  lp->media = _10Mb;
	      }
	      next_tick = dc2114x_autoconf(dev);
	  } else if (((lp->media == _100Mb) && is_100_up(dev)) ||
		     (((lp->media == _10Mb) || (lp->media == TP) ||
		       (lp->media == BNC)   || (lp->media == AUI)) &&
		      is_10_up(dev))) {
	      next_tick = dc2114x_autoconf(dev);
	  } else {
	      lp->tcount++;
	      lp->media = INIT;
	  }
	  break;

    case _10Mb:
        next_tick = 3000;
	if (!lp->tx_enable) {
	    SET_10Mb;
	    de4x5_init_connection(dev);
	} else {
	    if (!lp->linkOK && (lp->autosense == AUTO)) {
		if (!is_10_up(dev) || (!lp->useSROM && is_spd_100(dev))) {
		    lp->media = INIT;
		    lp->tcount++;
		    next_tick = DE4X5_AUTOSENSE_MS;
		}
	    }
	}
	break;

    case _100Mb:
        next_tick = 3000;
	if (!lp->tx_enable) {
	    SET_100Mb;
	    de4x5_init_connection(dev);
	} else {
	    if (!lp->linkOK && (lp->autosense == AUTO)) {
		if (!is_100_up(dev) || (!lp->useSROM && !is_spd_100(dev))) {
		    lp->media = INIT;
		    lp->tcount++;
		    next_tick = DE4X5_AUTOSENSE_MS;
		}
	    }
	}
	break;

    default:
	lp->tcount++;
printk("Huh?: media:%02x\n", lp->media);
	lp->media = INIT;
	break;
    }

    return next_tick;
}