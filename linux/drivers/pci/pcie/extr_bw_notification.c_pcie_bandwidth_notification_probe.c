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
struct pcie_device {int /*<<< orphan*/  port; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  pcie_bw_notification_handler ; 
 int /*<<< orphan*/  pcie_bw_notification_irq ; 
 int /*<<< orphan*/  pcie_enable_link_bandwidth_notification (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_link_bandwidth_notification_supported (int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pcie_device*) ; 

__attribute__((used)) static int pcie_bandwidth_notification_probe(struct pcie_device *srv)
{
	int ret;

	/* Single-width or single-speed ports do not have to support this. */
	if (!pcie_link_bandwidth_notification_supported(srv->port))
		return -ENODEV;

	ret = request_threaded_irq(srv->irq, pcie_bw_notification_irq,
				   pcie_bw_notification_handler,
				   IRQF_SHARED, "PCIe BW notif", srv);
	if (ret)
		return ret;

	pcie_enable_link_bandwidth_notification(srv->port);

	return 0;
}