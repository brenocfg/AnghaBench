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
typedef  scalar_t__ u32 ;
struct i40iw_sc_dev {int ceq_valid; } ;
struct i40iw_msix_vector {int dummy; } ;
struct i40iw_device {scalar_t__ ceqs_count; struct i40iw_sc_dev sc_dev; scalar_t__ msix_shared; struct i40iw_msix_vector* iw_msixtbl; struct i40iw_ceq* ceqlist; } ;
struct i40iw_ceq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_destroy_ceq (struct i40iw_device*,struct i40iw_ceq*) ; 
 int /*<<< orphan*/  i40iw_disable_irq (struct i40iw_sc_dev*,struct i40iw_msix_vector*,void*) ; 

__attribute__((used)) static void i40iw_dele_ceqs(struct i40iw_device *iwdev)
{
	u32 i = 0;
	struct i40iw_sc_dev *dev = &iwdev->sc_dev;
	struct i40iw_ceq *iwceq = iwdev->ceqlist;
	struct i40iw_msix_vector *msix_vec = iwdev->iw_msixtbl;

	if (iwdev->msix_shared) {
		i40iw_disable_irq(dev, msix_vec, (void *)iwdev);
		i40iw_destroy_ceq(iwdev, iwceq);
		iwceq++;
		i++;
	}

	for (msix_vec++; i < iwdev->ceqs_count; i++, msix_vec++, iwceq++) {
		i40iw_disable_irq(dev, msix_vec, (void *)iwceq);
		i40iw_destroy_ceq(iwdev, iwceq);
	}

	iwdev->sc_dev.ceq_valid = false;
}