#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct megasas_instance {size_t drv_buf_index; size_t drv_buf_alloc; size_t fw_crash_buffer_size; int /*<<< orphan*/  host; TYPE_3__* reg_set; int /*<<< orphan*/  fw_crash_state; TYPE_2__* pdev; TYPE_1__* instancet; int /*<<< orphan*/  crash_dump_buf; int /*<<< orphan*/ * crash_buf; } ;
struct TYPE_6__ {int /*<<< orphan*/  outbound_scratch_pad_0; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int (* read_fw_status_reg ) (struct megasas_instance*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AVAILABLE ; 
 int /*<<< orphan*/  CRASH_DMA_BUF_SIZE ; 
 int /*<<< orphan*/  MEGASAS_WAIT_FOR_NEXT_DMA_MSECS ; 
 int MEGASAS_WATCHDOG_WAIT_COUNT ; 
 int MFI_STATE_CRASH_DUMP_DONE ; 
 int MFI_STATE_DMADONE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  megasas_alloc_host_crash_buffer (struct megasas_instance*) ; 
 int /*<<< orphan*/  megasas_reset_fusion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int stub1 (struct megasas_instance*) ; 
 int stub2 (struct megasas_instance*) ; 
 int stub3 (struct megasas_instance*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void  megasas_fusion_crash_dump(struct megasas_instance *instance)
{
	u32 status_reg;
	u8 partial_copy = 0;
	int wait = 0;


	status_reg = instance->instancet->read_fw_status_reg(instance);

	/*
	 * Allocate host crash buffers to copy data from 1 MB DMA crash buffer
	 * to host crash buffers
	 */
	if (instance->drv_buf_index == 0) {
		/* Buffer is already allocated for old Crash dump.
		 * Do OCR and do not wait for crash dump collection
		 */
		if (instance->drv_buf_alloc) {
			dev_info(&instance->pdev->dev, "earlier crash dump is "
				"not yet copied by application, ignoring this "
				"crash dump and initiating OCR\n");
			status_reg |= MFI_STATE_CRASH_DUMP_DONE;
			writel(status_reg,
				&instance->reg_set->outbound_scratch_pad_0);
			readl(&instance->reg_set->outbound_scratch_pad_0);
			return;
		}
		megasas_alloc_host_crash_buffer(instance);
		dev_info(&instance->pdev->dev, "Number of host crash buffers "
			"allocated: %d\n", instance->drv_buf_alloc);
	}

	while (!(status_reg & MFI_STATE_CRASH_DUMP_DONE) &&
	       (wait < MEGASAS_WATCHDOG_WAIT_COUNT)) {
		if (!(status_reg & MFI_STATE_DMADONE)) {
			/*
			 * Next crash dump buffer is not yet DMA'd by FW
			 * Check after 10ms. Wait for 1 second for FW to
			 * post the next buffer. If not bail out.
			 */
			wait++;
			msleep(MEGASAS_WAIT_FOR_NEXT_DMA_MSECS);
			status_reg = instance->instancet->read_fw_status_reg(
					instance);
			continue;
		}

		wait = 0;
		if (instance->drv_buf_index >= instance->drv_buf_alloc) {
			dev_info(&instance->pdev->dev,
				 "Driver is done copying the buffer: %d\n",
				 instance->drv_buf_alloc);
			status_reg |= MFI_STATE_CRASH_DUMP_DONE;
			partial_copy = 1;
			break;
		} else {
			memcpy(instance->crash_buf[instance->drv_buf_index],
			       instance->crash_dump_buf, CRASH_DMA_BUF_SIZE);
			instance->drv_buf_index++;
			status_reg &= ~MFI_STATE_DMADONE;
		}

		writel(status_reg, &instance->reg_set->outbound_scratch_pad_0);
		readl(&instance->reg_set->outbound_scratch_pad_0);

		msleep(MEGASAS_WAIT_FOR_NEXT_DMA_MSECS);
		status_reg = instance->instancet->read_fw_status_reg(instance);
	}

	if (status_reg & MFI_STATE_CRASH_DUMP_DONE) {
		dev_info(&instance->pdev->dev, "Crash Dump is available,number "
			"of copied buffers: %d\n", instance->drv_buf_index);
		instance->fw_crash_buffer_size =  instance->drv_buf_index;
		instance->fw_crash_state = AVAILABLE;
		instance->drv_buf_index = 0;
		writel(status_reg, &instance->reg_set->outbound_scratch_pad_0);
		readl(&instance->reg_set->outbound_scratch_pad_0);
		if (!partial_copy)
			megasas_reset_fusion(instance->host, 0);
	}
}