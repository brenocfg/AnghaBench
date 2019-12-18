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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct genwqe_dev {struct pci_dev* pci_dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct genwqe_dev*) ; 
 int PTR_ERR (struct genwqe_dev*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct genwqe_dev*) ; 
 struct genwqe_dev* genwqe_dev_alloc () ; 
 int /*<<< orphan*/  genwqe_dev_free (struct genwqe_dev*) ; 
 int genwqe_health_check_start (struct genwqe_dev*) ; 
 int /*<<< orphan*/  genwqe_init_crc32 () ; 
 scalar_t__ genwqe_is_privileged (struct genwqe_dev*) ; 
 int /*<<< orphan*/  genwqe_pci_remove (struct genwqe_dev*) ; 
 int genwqe_pci_setup (struct genwqe_dev*) ; 
 int genwqe_start (struct genwqe_dev*) ; 
 int /*<<< orphan*/  genwqe_stop (struct genwqe_dev*) ; 

__attribute__((used)) static int genwqe_probe(struct pci_dev *pci_dev,
			const struct pci_device_id *id)
{
	int err;
	struct genwqe_dev *cd;

	genwqe_init_crc32();

	cd = genwqe_dev_alloc();
	if (IS_ERR(cd)) {
		dev_err(&pci_dev->dev, "err: could not alloc mem (err=%d)!\n",
			(int)PTR_ERR(cd));
		return PTR_ERR(cd);
	}

	dev_set_drvdata(&pci_dev->dev, cd);
	cd->pci_dev = pci_dev;

	err = genwqe_pci_setup(cd);
	if (err < 0) {
		dev_err(&pci_dev->dev,
			"err: problems with PCI setup (err=%d)\n", err);
		goto out_free_dev;
	}

	err = genwqe_start(cd);
	if (err < 0) {
		dev_err(&pci_dev->dev,
			"err: cannot start card services! (err=%d)\n", err);
		goto out_pci_remove;
	}

	if (genwqe_is_privileged(cd)) {
		err = genwqe_health_check_start(cd);
		if (err < 0) {
			dev_err(&pci_dev->dev,
				"err: cannot start health checking! (err=%d)\n",
				err);
			goto out_stop_services;
		}
	}
	return 0;

 out_stop_services:
	genwqe_stop(cd);
 out_pci_remove:
	genwqe_pci_remove(cd);
 out_free_dev:
	genwqe_dev_free(cd);
	return err;
}