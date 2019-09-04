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
 struct genwqe_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  genwqe_dev_free (struct genwqe_dev*) ; 
 int /*<<< orphan*/  genwqe_health_check_stop (struct genwqe_dev*) ; 
 int /*<<< orphan*/  genwqe_pci_remove (struct genwqe_dev*) ; 
 int /*<<< orphan*/  genwqe_stop (struct genwqe_dev*) ; 

__attribute__((used)) static void genwqe_remove(struct pci_dev *pci_dev)
{
	struct genwqe_dev *cd = dev_get_drvdata(&pci_dev->dev);

	genwqe_health_check_stop(cd);

	/*
	 * genwqe_stop() must survive if it is called twice
	 * sequentially. This happens when the health thread calls it
	 * and fails on genwqe_bus_reset().
	 */
	genwqe_stop(cd);
	genwqe_pci_remove(cd);
	genwqe_dev_free(cd);
}