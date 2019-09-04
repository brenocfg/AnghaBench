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
struct intel_data {int /*<<< orphan*/  flags; int /*<<< orphan*/  busy_work; } ;
struct hci_uart {struct intel_data* priv; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_TX_ACTIVE ; 
 int /*<<< orphan*/  bt_dev_dbg (struct hci_dev*,char*,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hci_uart* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_recv_lpm_notify(struct hci_dev *hdev, int value)
{
	struct hci_uart *hu = hci_get_drvdata(hdev);
	struct intel_data *intel = hu->priv;

	bt_dev_dbg(hdev, "TX idle notification (%d)", value);

	if (value) {
		set_bit(STATE_TX_ACTIVE, &intel->flags);
		schedule_work(&intel->busy_work);
	} else {
		clear_bit(STATE_TX_ACTIVE, &intel->flags);
	}
}