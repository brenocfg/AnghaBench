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
typedef  int /*<<< orphan*/  u16 ;
struct hl_device {struct goya_device* asic_specific; } ;
struct goya_device {int hw_cap_initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  GOYA_QUEUE_ID_CPU_PQ ; 
 int HW_CAP_CPU_Q ; 
 int hl_fw_send_cpu_message (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long*) ; 

int goya_send_cpu_message(struct hl_device *hdev, u32 *msg, u16 len,
				u32 timeout, long *result)
{
	struct goya_device *goya = hdev->asic_specific;

	if (!(goya->hw_cap_initialized & HW_CAP_CPU_Q)) {
		if (result)
			*result = 0;
		return 0;
	}

	return hl_fw_send_cpu_message(hdev, GOYA_QUEUE_ID_CPU_PQ, msg, len,
					timeout, result);
}