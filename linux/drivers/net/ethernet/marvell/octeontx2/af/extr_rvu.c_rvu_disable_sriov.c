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
struct rvu {int /*<<< orphan*/  pdev; int /*<<< orphan*/  afvf_wq_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_disable_sriov (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_disable_afvf_intr (struct rvu*) ; 
 int /*<<< orphan*/  rvu_mbox_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rvu_disable_sriov(struct rvu *rvu)
{
	rvu_disable_afvf_intr(rvu);
	rvu_mbox_destroy(&rvu->afvf_wq_info);
	pci_disable_sriov(rvu->pdev);
}