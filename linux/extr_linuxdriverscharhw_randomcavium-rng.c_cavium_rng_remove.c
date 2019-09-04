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
struct cavium_rng_pf {int /*<<< orphan*/  control_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_disable_sriov (struct pci_dev*) ; 
 struct cavium_rng_pf* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cavium_rng_remove(struct pci_dev *pdev)
{
	struct cavium_rng_pf *rng;

	rng = pci_get_drvdata(pdev);

	/* Remove the VF */
	pci_disable_sriov(pdev);

	/* Disable the RNG hardware and entropy source */
	writeq(0, rng->control_status);
}