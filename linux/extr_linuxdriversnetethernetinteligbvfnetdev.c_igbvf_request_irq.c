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
struct igbvf_adapter {TYPE_1__* pdev; scalar_t__ msix_entries; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int igbvf_request_msix (struct igbvf_adapter*) ; 

__attribute__((used)) static int igbvf_request_irq(struct igbvf_adapter *adapter)
{
	int err = -1;

	/* igbvf supports msi-x only */
	if (adapter->msix_entries)
		err = igbvf_request_msix(adapter);

	if (!err)
		return err;

	dev_err(&adapter->pdev->dev,
		"Unable to allocate interrupt, Error: %d\n", err);

	return err;
}