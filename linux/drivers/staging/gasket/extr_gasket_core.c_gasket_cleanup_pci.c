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
struct gasket_dev {int dummy; } ;

/* Variables and functions */
 int GASKET_NUM_BARS ; 
 int /*<<< orphan*/  gasket_unmap_pci_bar (struct gasket_dev*,int) ; 

__attribute__((used)) static void gasket_cleanup_pci(struct gasket_dev *gasket_dev)
{
	int i;

	for (i = 0; i < GASKET_NUM_BARS; i++)
		gasket_unmap_pci_bar(gasket_dev, i);
}