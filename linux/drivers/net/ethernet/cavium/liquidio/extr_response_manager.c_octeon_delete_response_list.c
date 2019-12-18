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
struct TYPE_3__ {int /*<<< orphan*/  work; } ;
struct TYPE_4__ {int /*<<< orphan*/  wq; TYPE_1__ wk; } ;
struct octeon_device {TYPE_2__ dma_comp_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 

void octeon_delete_response_list(struct octeon_device *oct)
{
	cancel_delayed_work_sync(&oct->dma_comp_wq.wk.work);
	destroy_workqueue(oct->dma_comp_wq.wq);
}