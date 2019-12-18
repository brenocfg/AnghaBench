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
typedef  int /*<<< orphan*/  u32 ;
struct hl_device {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */

__attribute__((used)) static u32 goya_get_pci_id(struct hl_device *hdev)
{
	return hdev->pdev->device;
}