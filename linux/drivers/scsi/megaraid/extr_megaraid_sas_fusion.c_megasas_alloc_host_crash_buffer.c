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
struct megasas_instance {unsigned int drv_buf_alloc; TYPE_1__* pdev; int /*<<< orphan*/ * crash_buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRASH_DMA_BUF_SIZE ; 
 unsigned int MAX_CRASH_DUMP_SIZE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  vzalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
megasas_alloc_host_crash_buffer(struct megasas_instance *instance)
{
	unsigned int i;

	for (i = 0; i < MAX_CRASH_DUMP_SIZE; i++) {
		instance->crash_buf[i] = vzalloc(CRASH_DMA_BUF_SIZE);
		if (!instance->crash_buf[i]) {
			dev_info(&instance->pdev->dev, "Firmware crash dump "
				"memory allocation failed at index %d\n", i);
			break;
		}
	}
	instance->drv_buf_alloc = i;
}