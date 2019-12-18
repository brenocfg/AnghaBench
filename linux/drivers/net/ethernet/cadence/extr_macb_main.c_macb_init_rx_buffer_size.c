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
struct macb {size_t rx_buffer_size; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 size_t MACB_RX_BUFFER_SIZE ; 
 int RX_BUFFER_MULTIPLE ; 
 int /*<<< orphan*/  macb_is_gem (struct macb*) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_1__*,char*,int,...) ; 
 int roundup (int,int) ; 

__attribute__((used)) static void macb_init_rx_buffer_size(struct macb *bp, size_t size)
{
	if (!macb_is_gem(bp)) {
		bp->rx_buffer_size = MACB_RX_BUFFER_SIZE;
	} else {
		bp->rx_buffer_size = size;

		if (bp->rx_buffer_size % RX_BUFFER_MULTIPLE) {
			netdev_dbg(bp->dev,
				   "RX buffer must be multiple of %d bytes, expanding\n",
				   RX_BUFFER_MULTIPLE);
			bp->rx_buffer_size =
				roundup(bp->rx_buffer_size, RX_BUFFER_MULTIPLE);
		}
	}

	netdev_dbg(bp->dev, "mtu [%u] rx_buffer_size [%zu]\n",
		   bp->dev->mtu, bp->rx_buffer_size);
}