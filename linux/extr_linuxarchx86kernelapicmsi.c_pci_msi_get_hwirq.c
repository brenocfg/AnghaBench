#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct msi_domain_info {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  msi_hwirq; } ;
typedef  TYPE_1__ msi_alloc_info_t ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */

__attribute__((used)) static irq_hw_number_t pci_msi_get_hwirq(struct msi_domain_info *info,
					 msi_alloc_info_t *arg)
{
	return arg->msi_hwirq;
}