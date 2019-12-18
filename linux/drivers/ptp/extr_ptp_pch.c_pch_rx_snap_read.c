#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct pch_dev {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_snap_hi; int /*<<< orphan*/  rx_snap_lo; } ;

/* Variables and functions */
 int TICKS_NS_SHIFT ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 struct pch_dev* pci_get_drvdata (struct pci_dev*) ; 

u64 pch_rx_snap_read(struct pci_dev *pdev)
{
	struct pch_dev *chip = pci_get_drvdata(pdev);
	u64 ns;
	u32 lo, hi;

	lo = ioread32(&chip->regs->rx_snap_lo);
	hi = ioread32(&chip->regs->rx_snap_hi);

	ns = ((u64) hi) << 32;
	ns |= lo;
	ns <<= TICKS_NS_SHIFT;

	return ns;
}