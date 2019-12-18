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
struct denali_controller {int /*<<< orphan*/  host; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  denali_remove (struct denali_controller*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct denali_controller* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void denali_pci_remove(struct pci_dev *dev)
{
	struct denali_controller *denali = pci_get_drvdata(dev);

	denali_remove(denali);
	iounmap(denali->reg);
	iounmap(denali->host);
}