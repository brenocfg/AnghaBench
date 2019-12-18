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
struct pci_dev {int dummy; } ;
struct ishtp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ish_device_disable (struct ishtp_device*) ; 
 int /*<<< orphan*/  ishtp_bus_remove_all_clients (struct ishtp_device*,int) ; 
 struct ishtp_device* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void ish_remove(struct pci_dev *pdev)
{
	struct ishtp_device *ishtp_dev = pci_get_drvdata(pdev);

	ishtp_bus_remove_all_clients(ishtp_dev, false);
	ish_device_disable(ishtp_dev);
}