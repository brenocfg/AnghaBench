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
struct i40iw_device {TYPE_1__* iw_msixtbl; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  ceqlist; scalar_t__ msix_shared; } ;
struct TYPE_2__ {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_enable_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_process_aeq (struct i40iw_device*) ; 
 int /*<<< orphan*/  i40iw_process_ceq (struct i40iw_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40iw_dpc(unsigned long data)
{
	struct i40iw_device *iwdev = (struct i40iw_device *)data;

	if (iwdev->msix_shared)
		i40iw_process_ceq(iwdev, iwdev->ceqlist);
	i40iw_process_aeq(iwdev);
	i40iw_enable_intr(&iwdev->sc_dev, iwdev->iw_msixtbl[0].idx);
}