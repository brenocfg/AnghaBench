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

/* Variables and functions */
 int /*<<< orphan*/ * _iobase ; 
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  geode_alg ; 
 int /*<<< orphan*/  geode_cbc_alg ; 
 int /*<<< orphan*/  geode_ecb_alg ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 

__attribute__((used)) static void geode_aes_remove(struct pci_dev *dev)
{
	crypto_unregister_alg(&geode_alg);
	crypto_unregister_alg(&geode_ecb_alg);
	crypto_unregister_alg(&geode_cbc_alg);

	pci_iounmap(dev, _iobase);
	_iobase = NULL;

	pci_release_regions(dev);
	pci_disable_device(dev);
}