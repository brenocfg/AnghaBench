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
struct agp_bridge_data {int /*<<< orphan*/  agp_in_use; } ;

/* Variables and functions */
 struct agp_bridge_data* agp_find_bridge (struct pci_dev*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

struct agp_bridge_data *agp_backend_acquire(struct pci_dev *pdev)
{
	struct agp_bridge_data *bridge;

	bridge = agp_find_bridge(pdev);

	if (!bridge)
		return NULL;

	if (atomic_read(&bridge->agp_in_use))
		return NULL;
	atomic_inc(&bridge->agp_in_use);
	return bridge;
}