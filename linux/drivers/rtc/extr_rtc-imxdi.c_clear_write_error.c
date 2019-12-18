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
struct imxdi_dev {TYPE_1__* pdev; scalar_t__ ioaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DSR ; 
 int DSR_WEF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void clear_write_error(struct imxdi_dev *imxdi)
{
	int cnt;

	dev_warn(&imxdi->pdev->dev, "WARNING: Register write error!\n");

	/* clear the write error flag */
	writel(DSR_WEF, imxdi->ioaddr + DSR);

	/* wait for it to take effect */
	for (cnt = 0; cnt < 1000; cnt++) {
		if ((readl(imxdi->ioaddr + DSR) & DSR_WEF) == 0)
			return;
		udelay(10);
	}
	dev_err(&imxdi->pdev->dev,
			"ERROR: Cannot clear write-error flag!\n");
}