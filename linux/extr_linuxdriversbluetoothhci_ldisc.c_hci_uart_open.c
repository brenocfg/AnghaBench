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
struct hci_dev {int /*<<< orphan*/  flush; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,struct hci_dev*) ; 
 int /*<<< orphan*/  hci_uart_flush ; 

__attribute__((used)) static int hci_uart_open(struct hci_dev *hdev)
{
	BT_DBG("%s %p", hdev->name, hdev);

	/* Undo clearing this from hci_uart_close() */
	hdev->flush = hci_uart_flush;

	return 0;
}