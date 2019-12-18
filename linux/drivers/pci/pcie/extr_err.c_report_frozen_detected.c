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

/* Variables and functions */
 int /*<<< orphan*/  pci_channel_io_frozen ; 
 int report_error_detected (struct pci_dev*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int report_frozen_detected(struct pci_dev *dev, void *data)
{
	return report_error_detected(dev, pci_channel_io_frozen, data);
}