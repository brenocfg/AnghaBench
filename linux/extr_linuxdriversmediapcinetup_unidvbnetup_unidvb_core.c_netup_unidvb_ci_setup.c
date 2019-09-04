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
struct netup_unidvb_dev {scalar_t__ bmmio0; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETUP_UNIDVB_IRQ_CI ; 
 scalar_t__ REG_IMASK_SET ; 
 int netup_unidvb_ci_register (struct netup_unidvb_dev*,int,struct pci_dev*) ; 
 int /*<<< orphan*/  netup_unidvb_ci_unregister (struct netup_unidvb_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int netup_unidvb_ci_setup(struct netup_unidvb_dev *ndev,
				 struct pci_dev *pci_dev)
{
	int res;

	writew(NETUP_UNIDVB_IRQ_CI, ndev->bmmio0 + REG_IMASK_SET);
	res = netup_unidvb_ci_register(ndev, 0, pci_dev);
	if (res)
		return res;
	res = netup_unidvb_ci_register(ndev, 1, pci_dev);
	if (res)
		netup_unidvb_ci_unregister(ndev, 0);
	return res;
}