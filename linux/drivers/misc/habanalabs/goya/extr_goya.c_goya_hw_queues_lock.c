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
struct hl_device {struct goya_device* asic_specific; } ;
struct goya_device {int /*<<< orphan*/  hw_queues_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void goya_hw_queues_lock(struct hl_device *hdev)
{
	struct goya_device *goya = hdev->asic_specific;

	spin_lock(&goya->hw_queues_lock);
}