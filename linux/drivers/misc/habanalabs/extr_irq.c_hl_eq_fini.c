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
struct hl_eq {scalar_t__ kernel_address; } ;
struct hl_device {TYPE_1__* asic_funcs; int /*<<< orphan*/  eq_wq; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cpu_accessible_dma_pool_free ) (struct hl_device*,int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HL_EQ_SIZE_IN_BYTES ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hl_device*,int /*<<< orphan*/ ,void*) ; 

void hl_eq_fini(struct hl_device *hdev, struct hl_eq *q)
{
	flush_workqueue(hdev->eq_wq);

	hdev->asic_funcs->cpu_accessible_dma_pool_free(hdev,
					HL_EQ_SIZE_IN_BYTES,
					(void *) (uintptr_t) q->kernel_address);
}