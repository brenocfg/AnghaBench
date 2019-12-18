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
struct pci_dev {TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 scalar_t__ ioc3_adjacent_is_ioc3 (struct pci_dev*,int) ; 

__attribute__((used)) static int ioc3_is_menet(struct pci_dev *pdev)
{
	return !pdev->bus->parent &&
	       ioc3_adjacent_is_ioc3(pdev, 0) &&
	       ioc3_adjacent_is_ioc3(pdev, 1) &&
	       ioc3_adjacent_is_ioc3(pdev, 2);
}