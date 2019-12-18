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
struct goya_device {int hw_cap_initialized; } ;

/* Variables and functions */
 int HW_CAP_CPU_Q ; 
 int hl_fw_test_cpu_queue (struct hl_device*) ; 

int goya_test_cpu_queue(struct hl_device *hdev)
{
	struct goya_device *goya = hdev->asic_specific;

	/*
	 * check capability here as send_cpu_message() won't update the result
	 * value if no capability
	 */
	if (!(goya->hw_cap_initialized & HW_CAP_CPU_Q))
		return 0;

	return hl_fw_test_cpu_queue(hdev);
}