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
struct fm10k_intfc {TYPE_1__* pdev; int /*<<< orphan*/  netdev; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_FLAG_RESET_REQUESTED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int fm10k_handle_reset (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_prepare_for_reset (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_reset_subtask(struct fm10k_intfc *interface)
{
	int err;

	if (!test_and_clear_bit(FM10K_FLAG_RESET_REQUESTED,
				interface->flags))
		return;

	/* If another thread has already prepared to reset the device, we
	 * should not attempt to handle a reset here, since we'd race with
	 * that thread. This may happen if we suspend the device or if the
	 * PCIe link is lost. In this case, we'll just ignore the RESET
	 * request, as it will (eventually) be taken care of when the thread
	 * which actually started the reset is finished.
	 */
	if (!fm10k_prepare_for_reset(interface))
		return;

	netdev_err(interface->netdev, "Reset interface\n");

	err = fm10k_handle_reset(interface);
	if (err)
		dev_err(&interface->pdev->dev,
			"fm10k_handle_reset failed: %d\n", err);
}