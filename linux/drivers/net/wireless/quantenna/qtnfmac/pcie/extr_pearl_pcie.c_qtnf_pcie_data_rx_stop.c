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
struct qtnf_pcie_pearl_state {int dummy; } ;
struct qtnf_bus {int /*<<< orphan*/  mux_napi; } ;

/* Variables and functions */
 scalar_t__ get_bus_priv (struct qtnf_bus*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qtnf_disable_hdp_irqs (struct qtnf_pcie_pearl_state*) ; 

__attribute__((used)) static void qtnf_pcie_data_rx_stop(struct qtnf_bus *bus)
{
	struct qtnf_pcie_pearl_state *ps = (void *)get_bus_priv(bus);

	napi_disable(&bus->mux_napi);
	qtnf_disable_hdp_irqs(ps);
}