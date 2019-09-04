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
typedef  int u8 ;
struct wbsd_host {int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 scalar_t__ WBSD_CSR ; 
 int WBSD_MSLED ; 
 int WBSD_WRPT ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct wbsd_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wbsd_get_ro(struct mmc_host *mmc)
{
	struct wbsd_host *host = mmc_priv(mmc);
	u8 csr;

	spin_lock_bh(&host->lock);

	csr = inb(host->base + WBSD_CSR);
	csr |= WBSD_MSLED;
	outb(csr, host->base + WBSD_CSR);

	mdelay(1);

	csr = inb(host->base + WBSD_CSR);
	csr &= ~WBSD_MSLED;
	outb(csr, host->base + WBSD_CSR);

	spin_unlock_bh(&host->lock);

	return !!(csr & WBSD_WRPT);
}