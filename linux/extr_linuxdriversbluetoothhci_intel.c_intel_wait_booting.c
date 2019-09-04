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
struct intel_data {int /*<<< orphan*/  flags; } ;
struct hci_uart {int /*<<< orphan*/  hdev; struct intel_data* priv; } ;

/* Variables and functions */
 int EINTR ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  STATE_BOOTING ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  bt_dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int wait_on_bit_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_wait_booting(struct hci_uart *hu)
{
	struct intel_data *intel = hu->priv;
	int err;

	err = wait_on_bit_timeout(&intel->flags, STATE_BOOTING,
				  TASK_INTERRUPTIBLE,
				  msecs_to_jiffies(1000));

	if (err == -EINTR) {
		bt_dev_err(hu->hdev, "Device boot interrupted");
		return -EINTR;
	}

	if (err) {
		bt_dev_err(hu->hdev, "Device boot timeout");
		return -ETIMEDOUT;
	}

	return err;
}