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

/* Variables and functions */
 int /*<<< orphan*/  qtnf_en_txdone_irq (struct qtnf_pcie_pearl_state*) ; 
 int /*<<< orphan*/  qtnf_pearl_data_tx_reclaim (struct qtnf_pcie_pearl_state*) ; 

__attribute__((used)) static void qtnf_pearl_reclaim_tasklet_fn(unsigned long data)
{
	struct qtnf_pcie_pearl_state *ps = (void *)data;

	qtnf_pearl_data_tx_reclaim(ps);
	qtnf_en_txdone_irq(ps);
}