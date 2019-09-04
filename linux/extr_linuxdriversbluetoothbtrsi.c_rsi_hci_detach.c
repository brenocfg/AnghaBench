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
struct rsi_hci_adapter {struct hci_dev* hdev; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_unregister_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree (struct rsi_hci_adapter*) ; 

__attribute__((used)) static void rsi_hci_detach(void *priv)
{
	struct rsi_hci_adapter *h_adapter = priv;
	struct hci_dev *hdev;

	if (!h_adapter)
		return;

	hdev = h_adapter->hdev;
	if (hdev) {
		hci_unregister_dev(hdev);
		hci_free_dev(hdev);
		h_adapter->hdev = NULL;
	}

	kfree(h_adapter);
}