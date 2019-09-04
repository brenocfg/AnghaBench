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
struct cavium_rng {int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwrng_unregister (int /*<<< orphan*/ *) ; 
 struct cavium_rng* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void  cavium_rng_remove_vf(struct pci_dev *pdev)
{
	struct cavium_rng *rng;

	rng = pci_get_drvdata(pdev);
	hwrng_unregister(&rng->ops);
}