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
struct qtnf_bus {int /*<<< orphan*/  mux_napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_rx_irqs (struct qtnf_pcie_topaz_state*) ; 
 struct qtnf_pcie_topaz_state* get_bus_priv (struct qtnf_bus*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qtnf_pcie_data_rx_start(struct qtnf_bus *bus)
{
	struct qtnf_pcie_topaz_state *ts = get_bus_priv(bus);

	napi_enable(&bus->mux_napi);
	enable_rx_irqs(ts);
}