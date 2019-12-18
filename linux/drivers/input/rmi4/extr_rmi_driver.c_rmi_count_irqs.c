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
struct rmi_device {int dummy; } ;
struct pdt_entry {scalar_t__ interrupt_source_count; } ;

/* Variables and functions */
 int RMI_SCAN_CONTINUE ; 
 int rmi_check_bootloader_mode (struct rmi_device*,struct pdt_entry const*) ; 

__attribute__((used)) static int rmi_count_irqs(struct rmi_device *rmi_dev,
			 void *ctx, const struct pdt_entry *pdt)
{
	int *irq_count = ctx;
	int ret;

	*irq_count += pdt->interrupt_source_count;

	ret = rmi_check_bootloader_mode(rmi_dev, pdt);
	if (ret < 0)
		return ret;

	return RMI_SCAN_CONTINUE;
}