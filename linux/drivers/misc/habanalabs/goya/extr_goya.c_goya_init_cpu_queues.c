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
typedef  scalar_t__ u32 ;
struct hl_hw_queue {int /*<<< orphan*/  bus_address; } ;
struct hl_eq {int /*<<< orphan*/  bus_address; } ;
struct hl_device {int /*<<< orphan*/  dev; struct hl_eq event_queue; int /*<<< orphan*/  cpu_queues_enable; struct hl_hw_queue* kernel_queues; struct goya_device* asic_specific; } ;
struct goya_device {int hw_cap_initialized; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GOYA_ASYNC_EVENT_ID_PI_UPDATE ; 
 int /*<<< orphan*/  GOYA_CPU_TIMEOUT_USEC ; 
 size_t GOYA_QUEUE_ID_CPU_PQ ; 
 int /*<<< orphan*/  HL_CPU_ACCESSIBLE_MEM_SIZE ; 
 int /*<<< orphan*/  HL_EQ_SIZE_IN_BYTES ; 
 int /*<<< orphan*/  HL_QUEUE_SIZE_IN_BYTES ; 
 int HW_CAP_CPU_Q ; 
 int /*<<< orphan*/  PQ_INIT_STATUS_READY_FOR_CP ; 
 scalar_t__ PQ_INIT_STATUS_READY_FOR_HOST ; 
 int /*<<< orphan*/  VA_CPU_ACCESSIBLE_MEM_ADDR ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int hl_poll_timeout (struct hl_device*,int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCPU_CQ_BASE_ADDR_HIGH ; 
 int /*<<< orphan*/  mmCPU_CQ_BASE_ADDR_LOW ; 
 int /*<<< orphan*/  mmCPU_CQ_LENGTH ; 
 int /*<<< orphan*/  mmCPU_EQ_BASE_ADDR_HIGH ; 
 int /*<<< orphan*/  mmCPU_EQ_BASE_ADDR_LOW ; 
 int /*<<< orphan*/  mmCPU_EQ_CI ; 
 int /*<<< orphan*/  mmCPU_EQ_LENGTH ; 
 int /*<<< orphan*/  mmCPU_IF_PF_PQ_PI ; 
 int /*<<< orphan*/  mmCPU_PQ_BASE_ADDR_HIGH ; 
 int /*<<< orphan*/  mmCPU_PQ_BASE_ADDR_LOW ; 
 int /*<<< orphan*/  mmCPU_PQ_INIT_STATUS ; 
 int /*<<< orphan*/  mmCPU_PQ_LENGTH ; 
 int /*<<< orphan*/  mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

int goya_init_cpu_queues(struct hl_device *hdev)
{
	struct goya_device *goya = hdev->asic_specific;
	struct hl_eq *eq;
	u32 status;
	struct hl_hw_queue *cpu_pq = &hdev->kernel_queues[GOYA_QUEUE_ID_CPU_PQ];
	int err;

	if (!hdev->cpu_queues_enable)
		return 0;

	if (goya->hw_cap_initialized & HW_CAP_CPU_Q)
		return 0;

	eq = &hdev->event_queue;

	WREG32(mmCPU_PQ_BASE_ADDR_LOW, lower_32_bits(cpu_pq->bus_address));
	WREG32(mmCPU_PQ_BASE_ADDR_HIGH, upper_32_bits(cpu_pq->bus_address));

	WREG32(mmCPU_EQ_BASE_ADDR_LOW, lower_32_bits(eq->bus_address));
	WREG32(mmCPU_EQ_BASE_ADDR_HIGH, upper_32_bits(eq->bus_address));

	WREG32(mmCPU_CQ_BASE_ADDR_LOW,
			lower_32_bits(VA_CPU_ACCESSIBLE_MEM_ADDR));
	WREG32(mmCPU_CQ_BASE_ADDR_HIGH,
			upper_32_bits(VA_CPU_ACCESSIBLE_MEM_ADDR));

	WREG32(mmCPU_PQ_LENGTH, HL_QUEUE_SIZE_IN_BYTES);
	WREG32(mmCPU_EQ_LENGTH, HL_EQ_SIZE_IN_BYTES);
	WREG32(mmCPU_CQ_LENGTH, HL_CPU_ACCESSIBLE_MEM_SIZE);

	/* Used for EQ CI */
	WREG32(mmCPU_EQ_CI, 0);

	WREG32(mmCPU_IF_PF_PQ_PI, 0);

	WREG32(mmCPU_PQ_INIT_STATUS, PQ_INIT_STATUS_READY_FOR_CP);

	WREG32(mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR,
			GOYA_ASYNC_EVENT_ID_PI_UPDATE);

	err = hl_poll_timeout(
		hdev,
		mmCPU_PQ_INIT_STATUS,
		status,
		(status == PQ_INIT_STATUS_READY_FOR_HOST),
		1000,
		GOYA_CPU_TIMEOUT_USEC);

	if (err) {
		dev_err(hdev->dev,
			"Failed to setup communication with device CPU\n");
		return -EIO;
	}

	goya->hw_cap_initialized |= HW_CAP_CPU_Q;
	return 0;
}