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
struct host1x {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void syncpt_enable_protection(struct host1x *host)
{
#if HOST1X_HW >= 6
	if (!host->hv_regs)
		return;

	host1x_hypervisor_writel(host, HOST1X_HV_SYNCPT_PROT_EN_CH_EN,
				 HOST1X_HV_SYNCPT_PROT_EN);
#endif
}