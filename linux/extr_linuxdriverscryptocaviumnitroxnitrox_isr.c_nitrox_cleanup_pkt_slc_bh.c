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
struct TYPE_2__ {struct bh_data* slc; } ;
struct nitrox_device {int nr_queues; TYPE_1__ bh; } ;
struct bh_data {int /*<<< orphan*/  resp_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct bh_data*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nitrox_cleanup_pkt_slc_bh(struct nitrox_device *ndev)
{
	int i;

	if (!ndev->bh.slc)
		return;

	for (i = 0; i < ndev->nr_queues; i++) {
		struct bh_data *bh = &ndev->bh.slc[i];

		tasklet_disable(&bh->resp_handler);
		tasklet_kill(&bh->resp_handler);
	}
	kfree(ndev->bh.slc);
	ndev->bh.slc = NULL;
}