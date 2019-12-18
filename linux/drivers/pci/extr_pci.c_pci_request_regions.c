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
 int pci_request_selected_regions (struct pci_dev*,int,char const*) ; 

int pci_request_regions(struct pci_dev *pdev, const char *res_name)
{
	return pci_request_selected_regions(pdev, ((1 << 6) - 1), res_name);
}