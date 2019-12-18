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
struct TYPE_2__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  work; } ;
struct bcmgenet_net_dim {scalar_t__ bytes; scalar_t__ packets; scalar_t__ event_ctr; TYPE_1__ dim; } ;
struct bcmgenet_rx_ring {struct bcmgenet_net_dim dim; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIM_CQ_PERIOD_MODE_START_FROM_EQE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,void (*) (struct work_struct*)) ; 

__attribute__((used)) static void bcmgenet_init_dim(struct bcmgenet_rx_ring *ring,
			      void (*cb)(struct work_struct *work))
{
	struct bcmgenet_net_dim *dim = &ring->dim;

	INIT_WORK(&dim->dim.work, cb);
	dim->dim.mode = DIM_CQ_PERIOD_MODE_START_FROM_EQE;
	dim->event_ctr = 0;
	dim->packets = 0;
	dim->bytes = 0;
}