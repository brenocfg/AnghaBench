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
struct hl_device {int mmu_enable; int cpu_enable; int fw_loading; int cpu_queues_enable; int heartbeat; scalar_t__ reset_pcilink; } ;

/* Variables and functions */

__attribute__((used)) static void set_driver_behavior_per_device(struct hl_device *hdev)
{
	hdev->mmu_enable = 1;
	hdev->cpu_enable = 1;
	hdev->fw_loading = 1;
	hdev->cpu_queues_enable = 1;
	hdev->heartbeat = 1;

	hdev->reset_pcilink = 0;
}