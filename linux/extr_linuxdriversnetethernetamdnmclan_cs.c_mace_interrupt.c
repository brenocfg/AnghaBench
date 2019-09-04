#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_errors; } ;
struct net_device {unsigned int base_addr; TYPE_1__ stats; } ;
struct TYPE_6__ {unsigned char xmtrc; int /*<<< orphan*/  mpco; int /*<<< orphan*/  rntpco; int /*<<< orphan*/  rcvcco; int /*<<< orphan*/  cerr; int /*<<< orphan*/  babl; int /*<<< orphan*/  jab; int /*<<< orphan*/  rtry; int /*<<< orphan*/  lcar; int /*<<< orphan*/  defer; int /*<<< orphan*/  one; int /*<<< orphan*/  more; int /*<<< orphan*/  lcol; int /*<<< orphan*/  uflo; int /*<<< orphan*/  xmtsv; int /*<<< orphan*/  exdef; } ;
struct TYPE_7__ {TYPE_2__ mace_stats; int /*<<< orphan*/  tx_free_frames; scalar_t__ tx_irq_disabled; } ;
typedef  TYPE_3__ mace_private ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ AM2150_MACE_BASE ; 
 scalar_t__ AM2150_XMT_SKIP ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ MACE_FIFOFC ; 
 unsigned char MACE_FIFOFC_XMTFC ; 
 scalar_t__ MACE_IMR ; 
 int MACE_IMR_DEFAULT ; 
 scalar_t__ MACE_IR ; 
 int MACE_IR_BABL ; 
 int MACE_IR_CERR ; 
 int MACE_IR_JAB ; 
 int MACE_IR_MPCO ; 
 int MACE_IR_RCVCCO ; 
 int MACE_IR_RCVINT ; 
 int MACE_IR_RNTPCO ; 
 int MACE_IR_XMTINT ; 
 int MACE_MAX_IR_ITERATIONS ; 
 int /*<<< orphan*/  MACE_MAX_RX_ITERATIONS ; 
 scalar_t__ MACE_XMTFS ; 
 unsigned char MACE_XMTFS_DEFER ; 
 unsigned char MACE_XMTFS_LCAR ; 
 unsigned char MACE_XMTFS_LCOL ; 
 unsigned char MACE_XMTFS_MORE ; 
 unsigned char MACE_XMTFS_ONE ; 
 unsigned char MACE_XMTFS_RTRY ; 
 unsigned char MACE_XMTFS_UFLO ; 
 unsigned char MACE_XMTFS_XMTSV ; 
 scalar_t__ MACE_XMTRC ; 
 unsigned char MACE_XMTRC_EXDEF ; 
 unsigned char MACE_XMTRC_XMTRC ; 
 void* inb (scalar_t__) ; 
 int /*<<< orphan*/  mace_rx (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*,char const*,void*,void*) ; 
 TYPE_3__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 

__attribute__((used)) static irqreturn_t mace_interrupt(int irq, void *dev_id)
{
  struct net_device *dev = (struct net_device *) dev_id;
  mace_private *lp = netdev_priv(dev);
  unsigned int ioaddr;
  int status;
  int IntrCnt = MACE_MAX_IR_ITERATIONS;

  if (dev == NULL) {
    pr_debug("mace_interrupt(): irq 0x%X for unknown device.\n",
	  irq);
    return IRQ_NONE;
  }

  ioaddr = dev->base_addr;

  if (lp->tx_irq_disabled) {
    const char *msg;
    if (lp->tx_irq_disabled)
      msg = "Interrupt with tx_irq_disabled";
    else
      msg = "Re-entering the interrupt handler";
    netdev_notice(dev, "%s [isr=%02X, imr=%02X]\n",
		  msg,
		  inb(ioaddr + AM2150_MACE_BASE + MACE_IR),
		  inb(ioaddr + AM2150_MACE_BASE + MACE_IMR));
    /* WARNING: MACE_IR has been read! */
    return IRQ_NONE;
  }

  if (!netif_device_present(dev)) {
    netdev_dbg(dev, "interrupt from dead card\n");
    return IRQ_NONE;
  }

  do {
    /* WARNING: MACE_IR is a READ/CLEAR port! */
    status = inb(ioaddr + AM2150_MACE_BASE + MACE_IR);
    if (!(status & ~MACE_IMR_DEFAULT) && IntrCnt == MACE_MAX_IR_ITERATIONS)
      return IRQ_NONE;

    pr_debug("mace_interrupt: irq 0x%X status 0x%X.\n", irq, status);

    if (status & MACE_IR_RCVINT) {
      mace_rx(dev, MACE_MAX_RX_ITERATIONS);
    }

    if (status & MACE_IR_XMTINT) {
      unsigned char fifofc;
      unsigned char xmtrc;
      unsigned char xmtfs;

      fifofc = inb(ioaddr + AM2150_MACE_BASE + MACE_FIFOFC);
      if ((fifofc & MACE_FIFOFC_XMTFC)==0) {
	dev->stats.tx_errors++;
	outb(0xFF, ioaddr + AM2150_XMT_SKIP);
      }

      /* Transmit Retry Count (XMTRC, reg 4) */
      xmtrc = inb(ioaddr + AM2150_MACE_BASE + MACE_XMTRC);
      if (xmtrc & MACE_XMTRC_EXDEF) lp->mace_stats.exdef++;
      lp->mace_stats.xmtrc += (xmtrc & MACE_XMTRC_XMTRC);

      if (
        (xmtfs = inb(ioaddr + AM2150_MACE_BASE + MACE_XMTFS)) &
        MACE_XMTFS_XMTSV /* Transmit Status Valid */
      ) {
	lp->mace_stats.xmtsv++;

	if (xmtfs & ~MACE_XMTFS_XMTSV) {
	  if (xmtfs & MACE_XMTFS_UFLO) {
	    /* Underflow.  Indicates that the Transmit FIFO emptied before
	       the end of frame was reached. */
	    lp->mace_stats.uflo++;
	  }
	  if (xmtfs & MACE_XMTFS_LCOL) {
	    /* Late Collision */
	    lp->mace_stats.lcol++;
	  }
	  if (xmtfs & MACE_XMTFS_MORE) {
	    /* MORE than one retry was needed */
	    lp->mace_stats.more++;
	  }
	  if (xmtfs & MACE_XMTFS_ONE) {
	    /* Exactly ONE retry occurred */
	    lp->mace_stats.one++;
	  }
	  if (xmtfs & MACE_XMTFS_DEFER) {
	    /* Transmission was defered */
	    lp->mace_stats.defer++;
	  }
	  if (xmtfs & MACE_XMTFS_LCAR) {
	    /* Loss of carrier */
	    lp->mace_stats.lcar++;
	  }
	  if (xmtfs & MACE_XMTFS_RTRY) {
	    /* Retry error: transmit aborted after 16 attempts */
	    lp->mace_stats.rtry++;
	  }
        } /* if (xmtfs & ~MACE_XMTFS_XMTSV) */

      } /* if (xmtfs & MACE_XMTFS_XMTSV) */

      dev->stats.tx_packets++;
      lp->tx_free_frames++;
      netif_wake_queue(dev);
    } /* if (status & MACE_IR_XMTINT) */

    if (status & ~MACE_IMR_DEFAULT & ~MACE_IR_RCVINT & ~MACE_IR_XMTINT) {
      if (status & MACE_IR_JAB) {
        /* Jabber Error.  Excessive transmit duration (20-150ms). */
        lp->mace_stats.jab++;
      }
      if (status & MACE_IR_BABL) {
        /* Babble Error.  >1518 bytes transmitted. */
        lp->mace_stats.babl++;
      }
      if (status & MACE_IR_CERR) {
	/* Collision Error.  CERR indicates the absence of the
	   Signal Quality Error Test message after a packet
	   transmission. */
        lp->mace_stats.cerr++;
      }
      if (status & MACE_IR_RCVCCO) {
        /* Receive Collision Count Overflow; */
        lp->mace_stats.rcvcco++;
      }
      if (status & MACE_IR_RNTPCO) {
        /* Runt Packet Count Overflow */
        lp->mace_stats.rntpco++;
      }
      if (status & MACE_IR_MPCO) {
        /* Missed Packet Count Overflow */
        lp->mace_stats.mpco++;
      }
    } /* if (status & ~MACE_IMR_DEFAULT & ~MACE_IR_RCVINT & ~MACE_IR_XMTINT) */

  } while ((status & ~MACE_IMR_DEFAULT) && (--IntrCnt));

  return IRQ_HANDLED;
}