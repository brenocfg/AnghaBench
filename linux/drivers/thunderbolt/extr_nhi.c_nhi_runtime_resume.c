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
struct tb_nhi {TYPE_1__* ops; } ;
struct tb {struct tb_nhi* nhi; } ;
struct pci_dev {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int (* runtime_resume ) (struct tb_nhi*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nhi_enable_int_throttling (struct tb_nhi*) ; 
 struct tb* pci_get_drvdata (struct pci_dev*) ; 
 int stub1 (struct tb_nhi*) ; 
 int tb_domain_runtime_resume (struct tb*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int nhi_runtime_resume(struct device *dev)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	struct tb *tb = pci_get_drvdata(pdev);
	struct tb_nhi *nhi = tb->nhi;
	int ret;

	if (nhi->ops && nhi->ops->runtime_resume) {
		ret = nhi->ops->runtime_resume(nhi);
		if (ret)
			return ret;
	}

	nhi_enable_int_throttling(nhi);
	return tb_domain_runtime_resume(tb);
}