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
struct qed_dev {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct qed_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_init_struct (struct qed_dev*) ; 

__attribute__((used)) static struct qed_dev *qed_alloc_cdev(struct pci_dev *pdev)
{
	struct qed_dev *cdev;

	cdev = kzalloc(sizeof(*cdev), GFP_KERNEL);
	if (!cdev)
		return cdev;

	qed_init_struct(cdev);

	return cdev;
}