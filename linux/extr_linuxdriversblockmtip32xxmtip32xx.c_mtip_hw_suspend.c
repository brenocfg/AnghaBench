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
struct driver_data {int /*<<< orphan*/  port; scalar_t__ mmio; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ HOST_CTL ; 
 int HOST_IRQ_EN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mtip_deinit_port (int /*<<< orphan*/ ) ; 
 scalar_t__ mtip_standby_drive (struct driver_data*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mtip_hw_suspend(struct driver_data *dd)
{
	/*
	 * Send standby immediate (E0h) to the drive
	 * so that it saves its state.
	 */
	if (mtip_standby_drive(dd) != 0) {
		dev_err(&dd->pdev->dev,
			"Failed standby-immediate command\n");
		return -EFAULT;
	}

	/* Disable interrupts on the HBA.*/
	writel(readl(dd->mmio + HOST_CTL) & ~HOST_IRQ_EN,
			dd->mmio + HOST_CTL);
	mtip_deinit_port(dd->port);

	return 0;
}