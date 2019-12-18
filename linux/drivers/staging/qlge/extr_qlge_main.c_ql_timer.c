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
typedef  int /*<<< orphan*/  u32 ;
struct timer_list {int dummy; } ;
struct ql_adapter {int /*<<< orphan*/  timer; int /*<<< orphan*/  ndev; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  STS ; 
 struct ql_adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifup ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_channel_offline (int /*<<< orphan*/ ) ; 
 struct ql_adapter* qdev ; 
 int /*<<< orphan*/  ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void ql_timer(struct timer_list *t)
{
	struct ql_adapter *qdev = from_timer(qdev, t, timer);
	u32 var = 0;

	var = ql_read32(qdev, STS);
	if (pci_channel_offline(qdev->pdev)) {
		netif_err(qdev, ifup, qdev->ndev, "EEH STS = 0x%.08x.\n", var);
		return;
	}

	mod_timer(&qdev->timer, jiffies + (5*HZ));
}