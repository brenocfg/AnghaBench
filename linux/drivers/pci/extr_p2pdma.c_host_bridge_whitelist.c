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
struct pci_host_bridge {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int __host_bridge_whitelist (struct pci_host_bridge*,int) ; 
 struct pci_host_bridge* pci_find_host_bridge (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool host_bridge_whitelist(struct pci_dev *a, struct pci_dev *b)
{
	struct pci_host_bridge *host_a = pci_find_host_bridge(a->bus);
	struct pci_host_bridge *host_b = pci_find_host_bridge(b->bus);

	if (host_a == host_b)
		return __host_bridge_whitelist(host_a, true);

	if (__host_bridge_whitelist(host_a, false) &&
	    __host_bridge_whitelist(host_b, false))
		return true;

	return false;
}