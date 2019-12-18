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
struct resource {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_unmap_iospace (struct resource*) ; 

__attribute__((used)) static void devm_pci_unmap_iospace(struct device *dev, void *ptr)
{
	struct resource **res = ptr;

	pci_unmap_iospace(*res);
}