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
struct uio_info {scalar_t__ priv; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread8 (scalar_t__) ; 

__attribute__((used)) static void print_board_data(struct pci_dev *pdev, struct uio_info *i)
{
	dev_info(&pdev->dev, "PCI-TC board vendor: %x%x number: %x%x"
		" revision: %c%c\n",
		ioread8(i->priv + 0x01),
		ioread8(i->priv + 0x00),
		ioread8(i->priv + 0x03),
		ioread8(i->priv + 0x02),
		ioread8(i->priv + 0x06),
		ioread8(i->priv + 0x07));
}