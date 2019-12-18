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
struct lima_device {int /*<<< orphan*/  empty_vm; int /*<<< orphan*/  dlbu_dma; scalar_t__ dlbu_cpu; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIMA_PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lima_clk_fini (struct lima_device*) ; 
 int /*<<< orphan*/  lima_fini_gp_pipe (struct lima_device*) ; 
 int /*<<< orphan*/  lima_fini_ip (struct lima_device*,int) ; 
 int /*<<< orphan*/  lima_fini_pp_pipe (struct lima_device*) ; 
 int lima_ip_num ; 
 int /*<<< orphan*/  lima_regulator_fini (struct lima_device*) ; 
 int /*<<< orphan*/  lima_vm_put (int /*<<< orphan*/ ) ; 

void lima_device_fini(struct lima_device *ldev)
{
	int i;

	lima_fini_pp_pipe(ldev);
	lima_fini_gp_pipe(ldev);

	for (i = lima_ip_num - 1; i >= 0; i--)
		lima_fini_ip(ldev, i);

	if (ldev->dlbu_cpu)
		dma_free_wc(ldev->dev, LIMA_PAGE_SIZE,
			    ldev->dlbu_cpu, ldev->dlbu_dma);

	lima_vm_put(ldev->empty_vm);

	lima_regulator_fini(ldev);

	lima_clk_fini(ldev);
}