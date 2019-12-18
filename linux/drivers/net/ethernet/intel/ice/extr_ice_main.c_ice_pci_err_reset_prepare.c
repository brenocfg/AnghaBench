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
struct ice_pf {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ICE_PFR_REQ ; 
 int /*<<< orphan*/  __ICE_PREPARED_FOR_RESET ; 
 int /*<<< orphan*/  __ICE_SUSPENDED ; 
 int /*<<< orphan*/  ice_prepare_for_reset (struct ice_pf*) ; 
 int /*<<< orphan*/  ice_service_task_stop (struct ice_pf*) ; 
 struct ice_pf* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_pci_err_reset_prepare(struct pci_dev *pdev)
{
	struct ice_pf *pf = pci_get_drvdata(pdev);

	if (!test_bit(__ICE_SUSPENDED, pf->state)) {
		ice_service_task_stop(pf);

		if (!test_bit(__ICE_PREPARED_FOR_RESET, pf->state)) {
			set_bit(__ICE_PFR_REQ, pf->state);
			ice_prepare_for_reset(pf);
		}
	}
}