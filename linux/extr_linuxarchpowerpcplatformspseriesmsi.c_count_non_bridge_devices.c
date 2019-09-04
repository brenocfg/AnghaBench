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
typedef  int u32 ;
struct msi_counts {int /*<<< orphan*/  num_devices; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int PCI_CLASS_BRIDGE_PCI ; 
 int be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct device_node*) ; 

__attribute__((used)) static void *count_non_bridge_devices(struct device_node *dn, void *data)
{
	struct msi_counts *counts = data;
	const __be32 *p;
	u32 class;

	pr_debug("rtas_msi: counting %pOF\n", dn);

	p = of_get_property(dn, "class-code", NULL);
	class = p ? be32_to_cpup(p) : 0;

	if ((class >> 8) != PCI_CLASS_BRIDGE_PCI)
		counts->num_devices++;

	return NULL;
}