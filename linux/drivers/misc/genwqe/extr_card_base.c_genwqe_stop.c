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
struct genwqe_dev {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  genwqe_device_remove (struct genwqe_dev*) ; 
 int /*<<< orphan*/  genwqe_ffdc_buffs_free (struct genwqe_dev*) ; 
 int /*<<< orphan*/  genwqe_finish_queue (struct genwqe_dev*) ; 
 scalar_t__ genwqe_is_privileged (struct genwqe_dev*) ; 
 int /*<<< orphan*/  genwqe_release_service_layer (struct genwqe_dev*) ; 
 int /*<<< orphan*/  pci_disable_sriov (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int genwqe_stop(struct genwqe_dev *cd)
{
	genwqe_finish_queue(cd);	    /* no register access */
	genwqe_device_remove(cd);	    /* device removed, procs killed */
	genwqe_release_service_layer(cd);   /* here genwqe_thread is stopped */

	if (genwqe_is_privileged(cd)) {
		pci_disable_sriov(cd->pci_dev);	/* access pci config space */
		genwqe_ffdc_buffs_free(cd);
	}

	return 0;
}