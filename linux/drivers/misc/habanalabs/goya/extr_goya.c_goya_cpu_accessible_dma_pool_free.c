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
struct hl_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hl_fw_cpu_accessible_dma_pool_free (struct hl_device*,size_t,void*) ; 

void goya_cpu_accessible_dma_pool_free(struct hl_device *hdev, size_t size,
					void *vaddr)
{
	hl_fw_cpu_accessible_dma_pool_free(hdev, size, vaddr);
}