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
struct sdricoh_host {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  R21C_STATUS ; 
 int /*<<< orphan*/  R224_MODE ; 
 int /*<<< orphan*/  R228_POWER ; 
 int /*<<< orphan*/  R2E0_INIT ; 
 int /*<<< orphan*/  R2F0_RESET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int sdricoh_readl (struct sdricoh_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdricoh_writel (struct sdricoh_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sdricoh_reset(struct sdricoh_host *host)
{
	dev_dbg(host->dev, "reset\n");
	sdricoh_writel(host, R2F0_RESET, 0x10001);
	sdricoh_writel(host, R2E0_INIT, 0x10000);
	if (sdricoh_readl(host, R2E0_INIT) != 0x10000)
		return -EIO;
	sdricoh_writel(host, R2E0_INIT, 0x10007);

	sdricoh_writel(host, R224_MODE, 0x2000000);
	sdricoh_writel(host, R228_POWER, 0xe0);


	/* status register ? */
	sdricoh_writel(host, R21C_STATUS, 0x18);

	return 0;
}