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
struct pci_dev {int dummy; } ;
struct gasket_internal_desc {TYPE_1__* driver_desc; } ;
struct TYPE_2__ {scalar_t__ pci_id_table; } ;

/* Variables and functions */
 int GASKET_FRAMEWORK_DESC_MAX ; 
 int /*<<< orphan*/  __must_hold (int /*<<< orphan*/ *) ; 
 struct gasket_internal_desc* g_descs ; 
 int /*<<< orphan*/  g_mutex ; 
 scalar_t__ pci_match_id (scalar_t__,struct pci_dev*) ; 

__attribute__((used)) static struct gasket_internal_desc *
lookup_pci_internal_desc(struct pci_dev *pci_dev)
{
	int i;

	__must_hold(&g_mutex);
	for (i = 0; i < GASKET_FRAMEWORK_DESC_MAX; i++) {
		if (g_descs[i].driver_desc &&
		    g_descs[i].driver_desc->pci_id_table &&
		    pci_match_id(g_descs[i].driver_desc->pci_id_table, pci_dev))
			return &g_descs[i];
	}

	return NULL;
}