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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct octeon_i2c {int /*<<< orphan*/  adap; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct octeon_i2c* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  thunder_i2c_clock_disable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thunder_i2c_smbus_remove (struct octeon_i2c*) ; 

__attribute__((used)) static void thunder_i2c_remove_pci(struct pci_dev *pdev)
{
	struct octeon_i2c *i2c = pci_get_drvdata(pdev);

	thunder_i2c_smbus_remove(i2c);
	thunder_i2c_clock_disable(&pdev->dev, i2c->clk);
	i2c_del_adapter(&i2c->adap);
}