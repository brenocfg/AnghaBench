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
struct qtnf_pcie_topaz_state {int dummy; } ;
struct qtnf_bus {int dummy; } ;

/* Variables and functions */
 struct qtnf_pcie_topaz_state* get_bus_priv (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_topaz_free_xfer_buffers (struct qtnf_pcie_topaz_state*) ; 
 int /*<<< orphan*/  qtnf_topaz_reset_ep (struct qtnf_pcie_topaz_state*) ; 

__attribute__((used)) static void qtnf_pcie_topaz_remove(struct qtnf_bus *bus)
{
	struct qtnf_pcie_topaz_state *ts = get_bus_priv(bus);

	qtnf_topaz_reset_ep(ts);
	qtnf_topaz_free_xfer_buffers(ts);
}