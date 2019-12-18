#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
struct rx_ring_info {int /*<<< orphan*/  rx_channel; } ;
struct niu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RX_DMA_CTL_STAT (int /*<<< orphan*/ ) ; 
 int RX_DMA_CTL_STAT_CHAN_FATAL ; 
 int RX_DMA_CTL_STAT_PORT_FATAL ; 
 int RX_DMA_CTL_WRITE_CLEAR_ERRS ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  niu_log_rxchan_errors (struct niu*,struct rx_ring_info*,int) ; 
 int nr64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int niu_rx_error(struct niu *np, struct rx_ring_info *rp)
{
	u64 stat = nr64(RX_DMA_CTL_STAT(rp->rx_channel));
	int err = 0;


	if (stat & (RX_DMA_CTL_STAT_CHAN_FATAL |
		    RX_DMA_CTL_STAT_PORT_FATAL))
		err = -EINVAL;

	if (err) {
		netdev_err(np->dev, "RX channel %u error, stat[%llx]\n",
			   rp->rx_channel,
			   (unsigned long long) stat);

		niu_log_rxchan_errors(np, rp, stat);
	}

	nw64(RX_DMA_CTL_STAT(rp->rx_channel),
	     stat & RX_DMA_CTL_WRITE_CLEAR_ERRS);

	return err;
}