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
struct virtqueue {TYPE_1__* vdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_kicks; } ;
struct cfv_info {int /*<<< orphan*/  tx_release_tasklet; TYPE_2__ stats; } ;
struct TYPE_3__ {struct cfv_info* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cfv_release_cb(struct virtqueue *vq_tx)
{
	struct cfv_info *cfv = vq_tx->vdev->priv;

	++cfv->stats.tx_kicks;
	tasklet_schedule(&cfv->tx_release_tasklet);
}