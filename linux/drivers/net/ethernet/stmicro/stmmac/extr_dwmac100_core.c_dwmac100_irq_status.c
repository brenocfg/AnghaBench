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
struct stmmac_extra_stats {int dummy; } ;
struct mac_device_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int dwmac100_irq_status(struct mac_device_info *hw,
			       struct stmmac_extra_stats *x)
{
	return 0;
}