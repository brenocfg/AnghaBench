#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tx_heartbeat_errors; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_aborted_errors; scalar_t__ rx_missed_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; scalar_t__ rx_length_errors; scalar_t__ collisions; } ;
struct net_device {TYPE_1__ stats; } ;
struct TYPE_7__ {int rcvcco; int rntpco; int mpco; int /*<<< orphan*/  cerr; int /*<<< orphan*/  uflo; int /*<<< orphan*/  lcar; int /*<<< orphan*/  rtry; scalar_t__ mpc; int /*<<< orphan*/  oflo; int /*<<< orphan*/  fram; int /*<<< orphan*/  fcs; scalar_t__ rntpc; scalar_t__ rcvcc; } ;
struct TYPE_8__ {TYPE_2__ mace_stats; } ;
typedef  TYPE_3__ mace_private ;

/* Variables and functions */
 int /*<<< orphan*/  MACE_MPC ; 
 int /*<<< orphan*/  MACE_RCVCC ; 
 int /*<<< orphan*/  MACE_RNTPC ; 
 scalar_t__ mace_read (TYPE_3__*,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_3__* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void update_stats(unsigned int ioaddr, struct net_device *dev)
{
  mace_private *lp = netdev_priv(dev);

  lp->mace_stats.rcvcc += mace_read(lp, ioaddr, MACE_RCVCC);
  lp->mace_stats.rntpc += mace_read(lp, ioaddr, MACE_RNTPC);
  lp->mace_stats.mpc += mace_read(lp, ioaddr, MACE_MPC);
  /* At this point, mace_stats is fully updated for this call.
     We may now update the netdev stats. */

  /* The MACE has no equivalent for netdev stats field which are commented
     out. */

  /* dev->stats.multicast; */
  dev->stats.collisions =
    lp->mace_stats.rcvcco * 256 + lp->mace_stats.rcvcc;
    /* Collision: The MACE may retry sending a packet 15 times
       before giving up.  The retry count is in XMTRC.
       Does each retry constitute a collision?
       If so, why doesn't the RCVCC record these collisions? */

  /* detailed rx_errors: */
  dev->stats.rx_length_errors =
    lp->mace_stats.rntpco * 256 + lp->mace_stats.rntpc;
  /* dev->stats.rx_over_errors */
  dev->stats.rx_crc_errors = lp->mace_stats.fcs;
  dev->stats.rx_frame_errors = lp->mace_stats.fram;
  dev->stats.rx_fifo_errors = lp->mace_stats.oflo;
  dev->stats.rx_missed_errors =
    lp->mace_stats.mpco * 256 + lp->mace_stats.mpc;

  /* detailed tx_errors */
  dev->stats.tx_aborted_errors = lp->mace_stats.rtry;
  dev->stats.tx_carrier_errors = lp->mace_stats.lcar;
    /* LCAR usually results from bad cabling. */
  dev->stats.tx_fifo_errors = lp->mace_stats.uflo;
  dev->stats.tx_heartbeat_errors = lp->mace_stats.cerr;
  /* dev->stats.tx_window_errors; */
}