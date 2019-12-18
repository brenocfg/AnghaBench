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
typedef  int u32 ;
struct rocker_port {int /*<<< orphan*/  rx_ring; TYPE_2__* dev; struct rocker* rocker; } ;
struct rocker_desc_info {int dummy; } ;
struct rocker {int dummy; } ;
struct napi_struct {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_errors; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_complete_done (struct napi_struct*,int) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_err (TYPE_2__*,char*,int) ; 
 int rocker_desc_err (struct rocker_desc_info*) ; 
 int /*<<< orphan*/  rocker_desc_gen_clear (struct rocker_desc_info*) ; 
 int /*<<< orphan*/  rocker_desc_head_set (struct rocker const*,int /*<<< orphan*/ *,struct rocker_desc_info*) ; 
 struct rocker_desc_info* rocker_desc_tail_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rocker_dma_ring_credits_set (struct rocker const*,int /*<<< orphan*/ *,int) ; 
 struct rocker_port* rocker_port_napi_rx_get (struct napi_struct*) ; 
 int rocker_port_rx_proc (struct rocker const*,struct rocker_port*,struct rocker_desc_info*) ; 

__attribute__((used)) static int rocker_port_poll_rx(struct napi_struct *napi, int budget)
{
	struct rocker_port *rocker_port = rocker_port_napi_rx_get(napi);
	const struct rocker *rocker = rocker_port->rocker;
	struct rocker_desc_info *desc_info;
	u32 credits = 0;
	int err;

	/* Process rx descriptors */
	while (credits < budget &&
	       (desc_info = rocker_desc_tail_get(&rocker_port->rx_ring))) {
		err = rocker_desc_err(desc_info);
		if (err) {
			if (net_ratelimit())
				netdev_err(rocker_port->dev, "rx desc received with err %d\n",
					   err);
		} else {
			err = rocker_port_rx_proc(rocker, rocker_port,
						  desc_info);
			if (err && net_ratelimit())
				netdev_err(rocker_port->dev, "rx processing failed with err %d\n",
					   err);
		}
		if (err)
			rocker_port->dev->stats.rx_errors++;

		rocker_desc_gen_clear(desc_info);
		rocker_desc_head_set(rocker, &rocker_port->rx_ring, desc_info);
		credits++;
	}

	if (credits < budget)
		napi_complete_done(napi, credits);

	rocker_dma_ring_credits_set(rocker, &rocker_port->rx_ring, credits);

	return credits;
}