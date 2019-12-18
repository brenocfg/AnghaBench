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
struct amd_ntb_dev {int /*<<< orphan*/  hb_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ndev_deinit_isr (struct amd_ntb_dev*) ; 

__attribute__((used)) static void amd_deinit_dev(struct amd_ntb_dev *ndev)
{
	cancel_delayed_work_sync(&ndev->hb_timer);

	ndev_deinit_isr(ndev);
}