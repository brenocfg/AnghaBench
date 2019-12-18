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
struct hv_pci_dev {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hv_pci_dev*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_pcichild(struct hv_pci_dev *hpdev)
{
	if (refcount_dec_and_test(&hpdev->refs))
		kfree(hpdev);
}