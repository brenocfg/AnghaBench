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
struct qed_dev {int dummy; } ;
typedef  int /*<<< orphan*/  pci_power_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int /*<<< orphan*/ ,char*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  NETIF_MSG_DRV ; 

__attribute__((used)) static int qed_set_power_state(struct qed_dev *cdev, pci_power_t state)
{
	if (!cdev)
		return -ENODEV;

	DP_VERBOSE(cdev, NETIF_MSG_DRV, "Omitting Power state change\n");
	return 0;
}