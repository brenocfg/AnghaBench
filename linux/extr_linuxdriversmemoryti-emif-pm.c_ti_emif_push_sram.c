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
struct ti_emif_data {int /*<<< orphan*/  pm_data; int /*<<< orphan*/  sram_pool_code; scalar_t__ ti_emif_sram_virt; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* sram_exec_copy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ sram_suspend_address (struct ti_emif_data*,unsigned long) ; 
 int /*<<< orphan*/  ti_emif_pm_sram_data ; 
 int /*<<< orphan*/  ti_emif_sram ; 
 int ti_emif_sram_sz ; 

__attribute__((used)) static int ti_emif_push_sram(struct device *dev, struct ti_emif_data *emif_data)
{
	void *copy_addr;
	u32 data_addr;

	copy_addr = sram_exec_copy(emif_data->sram_pool_code,
				   (void *)emif_data->ti_emif_sram_virt,
				   &ti_emif_sram, ti_emif_sram_sz);
	if (!copy_addr) {
		dev_err(dev, "Cannot copy emif code to sram\n");
		return -ENODEV;
	}

	data_addr = sram_suspend_address(emif_data,
					 (unsigned long)&ti_emif_pm_sram_data);
	copy_addr = sram_exec_copy(emif_data->sram_pool_code,
				   (void *)data_addr,
				   &emif_data->pm_data,
				   sizeof(emif_data->pm_data));
	if (!copy_addr) {
		dev_err(dev, "Cannot copy emif data to code sram\n");
		return -ENODEV;
	}

	return 0;
}