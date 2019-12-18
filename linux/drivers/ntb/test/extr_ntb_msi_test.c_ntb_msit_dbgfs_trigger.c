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
typedef  size_t u64 ;
struct ntb_msit_peer {size_t num_irqs; int /*<<< orphan*/ * msi_desc; int /*<<< orphan*/  pidx; TYPE_1__* nm; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {TYPE_2__* ntb; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ ) ; 
 int ntb_msi_peer_trigger (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ntb_msit_dbgfs_trigger(void *data, u64 idx)
{
	struct ntb_msit_peer *peer = data;

	if (idx >= peer->num_irqs)
		return -EINVAL;

	dev_dbg(&peer->nm->ntb->dev, "trigger irq %llu on peer %u\n",
		idx, peer->pidx);

	return ntb_msi_peer_trigger(peer->nm->ntb, peer->pidx,
				    &peer->msi_desc[idx]);
}