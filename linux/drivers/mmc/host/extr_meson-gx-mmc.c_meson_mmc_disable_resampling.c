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
struct meson_host {TYPE_1__* data; scalar_t__ regs; } ;
struct TYPE_2__ {scalar_t__ adjust; } ;

/* Variables and functions */
 unsigned int ADJUST_ADJ_EN ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void meson_mmc_disable_resampling(struct meson_host *host)
{
	unsigned int val = readl(host->regs + host->data->adjust);

	val &= ~ADJUST_ADJ_EN;
	writel(val, host->regs + host->data->adjust);
}