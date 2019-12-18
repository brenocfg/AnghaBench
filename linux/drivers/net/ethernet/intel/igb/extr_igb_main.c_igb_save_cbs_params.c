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
struct igb_ring {int cbs_enable; int idleslope; int sendslope; int hicredit; int locredit; } ;
struct igb_adapter {int num_tx_queues; struct igb_ring** tx_ring; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int igb_save_cbs_params(struct igb_adapter *adapter, int queue,
			       bool enable, int idleslope, int sendslope,
			       int hicredit, int locredit)
{
	struct igb_ring *ring;

	if (queue < 0 || queue > adapter->num_tx_queues)
		return -EINVAL;

	ring = adapter->tx_ring[queue];

	ring->cbs_enable = enable;
	ring->idleslope = idleslope;
	ring->sendslope = sendslope;
	ring->hicredit = hicredit;
	ring->locredit = locredit;

	return 0;
}