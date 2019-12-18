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
struct i40iw_device {int /*<<< orphan*/  sc_dev; } ;
struct i40iw_ceq {int /*<<< orphan*/  msix_idx; struct i40iw_device* iwdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_enable_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_process_ceq (struct i40iw_device*,struct i40iw_ceq*) ; 

__attribute__((used)) static void i40iw_ceq_dpc(unsigned long data)
{
	struct i40iw_ceq *iwceq = (struct i40iw_ceq *)data;
	struct i40iw_device *iwdev = iwceq->iwdev;

	i40iw_process_ceq(iwdev, iwceq);
	i40iw_enable_intr(&iwdev->sc_dev, iwceq->msix_idx);
}