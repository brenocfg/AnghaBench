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

/* Variables and functions */
 int /*<<< orphan*/  qtnf_topaz_data_tx_reclaim (struct qtnf_pcie_topaz_state*) ; 

__attribute__((used)) static void qtnf_reclaim_tasklet_fn(unsigned long data)
{
	struct qtnf_pcie_topaz_state *ts = (void *)data;

	qtnf_topaz_data_tx_reclaim(ts);
}