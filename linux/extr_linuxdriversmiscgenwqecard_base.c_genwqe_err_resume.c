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
struct genwqe_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct genwqe_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int genwqe_health_check_start (struct genwqe_dev*) ; 
 int genwqe_start (struct genwqe_dev*) ; 

__attribute__((used)) static void genwqe_err_resume(struct pci_dev *pci_dev)
{
	int rc;
	struct genwqe_dev *cd = dev_get_drvdata(&pci_dev->dev);

	rc = genwqe_start(cd);
	if (!rc) {
		rc = genwqe_health_check_start(cd);
		if (rc)
			dev_err(&pci_dev->dev,
				"err: cannot start health checking! (err=%d)\n",
				rc);
	} else {
		dev_err(&pci_dev->dev,
			"err: cannot start card services! (err=%d)\n", rc);
	}
}