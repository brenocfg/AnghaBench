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
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_add_resource_offset (struct list_head*,struct resource*,int /*<<< orphan*/ ) ; 

void pci_add_resource(struct list_head *resources, struct resource *res)
{
	pci_add_resource_offset(resources, res, 0);
}