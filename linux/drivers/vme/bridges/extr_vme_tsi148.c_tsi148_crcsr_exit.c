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
typedef  int u32 ;
struct vme_bridge {struct tsi148_driver* driver_priv; } ;
struct tsi148_driver {int /*<<< orphan*/  crcsr_bus; int /*<<< orphan*/  crcsr_kernel; scalar_t__ base; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ TSI148_LCSR_CRAT ; 
 int TSI148_LCSR_CRAT_EN ; 
 scalar_t__ TSI148_LCSR_CROL ; 
 scalar_t__ TSI148_LCSR_CROU ; 
 int /*<<< orphan*/  VME_CRCSR_BUF_SIZE ; 
 int ioread32be (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32be (int,scalar_t__) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tsi148_crcsr_exit(struct vme_bridge *tsi148_bridge,
	struct pci_dev *pdev)
{
	u32 crat;
	struct tsi148_driver *bridge;

	bridge = tsi148_bridge->driver_priv;

	/* Turn off CR/CSR space */
	crat = ioread32be(bridge->base + TSI148_LCSR_CRAT);
	iowrite32be(crat & ~TSI148_LCSR_CRAT_EN,
		bridge->base + TSI148_LCSR_CRAT);

	/* Free image */
	iowrite32be(0, bridge->base + TSI148_LCSR_CROU);
	iowrite32be(0, bridge->base + TSI148_LCSR_CROL);

	pci_free_consistent(pdev, VME_CRCSR_BUF_SIZE, bridge->crcsr_kernel,
		bridge->crcsr_bus);
}