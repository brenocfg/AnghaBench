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
struct jmb38x_ms_host {scalar_t__ addr; TYPE_2__* chip; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ HOST_CONTROL ; 
 int HOST_CONTROL_CLOCK_EN ; 
 int HOST_CONTROL_RESET ; 
 int HOST_CONTROL_RESET_REQ ; 
 scalar_t__ INT_SIGNAL_ENABLE ; 
 int INT_STATUS_ALL ; 
 scalar_t__ INT_STATUS_ENABLE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int jmb38x_ms_reset(struct jmb38x_ms_host *host)
{
	int cnt;

	writel(HOST_CONTROL_RESET_REQ | HOST_CONTROL_CLOCK_EN
	       | readl(host->addr + HOST_CONTROL),
	       host->addr + HOST_CONTROL);

	for (cnt = 0; cnt < 20; ++cnt) {
		if (!(HOST_CONTROL_RESET_REQ
		      & readl(host->addr + HOST_CONTROL)))
			goto reset_next;

		ndelay(20);
	}
	dev_dbg(&host->chip->pdev->dev, "reset_req timeout\n");

reset_next:
	writel(HOST_CONTROL_RESET | HOST_CONTROL_CLOCK_EN
	       | readl(host->addr + HOST_CONTROL),
	       host->addr + HOST_CONTROL);

	for (cnt = 0; cnt < 20; ++cnt) {
		if (!(HOST_CONTROL_RESET
		      & readl(host->addr + HOST_CONTROL)))
			goto reset_ok;

		ndelay(20);
	}
	dev_dbg(&host->chip->pdev->dev, "reset timeout\n");
	return -EIO;

reset_ok:
	writel(INT_STATUS_ALL, host->addr + INT_SIGNAL_ENABLE);
	writel(INT_STATUS_ALL, host->addr + INT_STATUS_ENABLE);
	return 0;
}