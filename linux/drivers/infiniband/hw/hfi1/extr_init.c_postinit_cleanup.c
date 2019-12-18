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
struct hfi1_devdata {int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_device_data (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  hfi1_comp_vectors_clean_up (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  hfi1_dev_affinity_clean_up (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  hfi1_free_devdata (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  hfi1_pcie_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_pcie_ddcleanup (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  hfi1_start_cleanup (struct hfi1_devdata*) ; 

__attribute__((used)) static void postinit_cleanup(struct hfi1_devdata *dd)
{
	hfi1_start_cleanup(dd);
	hfi1_comp_vectors_clean_up(dd);
	hfi1_dev_affinity_clean_up(dd);

	hfi1_pcie_ddcleanup(dd);
	hfi1_pcie_cleanup(dd->pcidev);

	cleanup_device_data(dd);

	hfi1_free_devdata(dd);
}