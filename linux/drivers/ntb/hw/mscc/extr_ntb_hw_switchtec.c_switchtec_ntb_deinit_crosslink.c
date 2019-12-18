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
struct switchtec_ntb {scalar_t__ mmio_xlink_win; TYPE_1__* stdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_iounmap (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void switchtec_ntb_deinit_crosslink(struct switchtec_ntb *sndev)
{
	if (sndev->mmio_xlink_win)
		pci_iounmap(sndev->stdev->pdev, sndev->mmio_xlink_win);
}