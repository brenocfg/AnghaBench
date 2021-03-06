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
struct pcie_device {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcie_disable_link_bandwidth_notification (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcie_bandwidth_notification_suspend(struct pcie_device *srv)
{
	pcie_disable_link_bandwidth_notification(srv->port);
	return 0;
}