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
typedef  size_t u64 ;
struct TYPE_2__ {int /*<<< orphan*/  (* napi_fn ) (struct octeon_droq*) ;scalar_t__ poll_mode; } ;
struct octeon_droq {TYPE_1__ ops; } ;
struct octeon_device_priv {int napi_mask; int /*<<< orphan*/  droq_tasklet; } ;
struct octeon_device {int int_status; int droq_intr; struct octeon_droq** droq; scalar_t__ priv; } ;

/* Variables and functions */
 int BIT_ULL (size_t) ; 
 size_t MAX_OCTEON_OUTPUT_QUEUES (struct octeon_device*) ; 
 int OCT_DEV_INTR_PKT_DATA ; 
 int /*<<< orphan*/  stub1 (struct octeon_droq*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void liquidio_schedule_droq_pkt_handlers(struct octeon_device *oct)
{
	struct octeon_device_priv *oct_priv =
		(struct octeon_device_priv *)oct->priv;
	struct octeon_droq *droq;
	u64 oq_no;

	if (oct->int_status & OCT_DEV_INTR_PKT_DATA) {
		for (oq_no = 0; oq_no < MAX_OCTEON_OUTPUT_QUEUES(oct);
		     oq_no++) {
			if (!(oct->droq_intr & BIT_ULL(oq_no)))
				continue;

			droq = oct->droq[oq_no];

			if (droq->ops.poll_mode) {
				droq->ops.napi_fn(droq);
				oct_priv->napi_mask |= BIT_ULL(oq_no);
			} else {
				tasklet_schedule(&oct_priv->droq_tasklet);
			}
		}
	}
}