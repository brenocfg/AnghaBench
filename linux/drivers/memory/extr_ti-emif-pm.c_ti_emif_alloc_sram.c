#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* regs_phys; struct emif_regs_amx3* regs_virt; } ;
struct TYPE_3__ {void* run_hw_leveling; void* exit_sr; void* restore_context; void* abort_sr; void* enter_sr; void* save_context; } ;
struct ti_emif_data {void* ti_emif_sram_virt; void* sram_pool_code; void* ti_emif_sram_data_phys; TYPE_2__ pm_data; void* ti_emif_sram_data_virt; TYPE_1__ pm_functions; void* sram_pool_data; void* ti_emif_sram_phys; } ;
struct emif_regs_amx3 {int dummy; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* gen_pool_alloc (void*,int) ; 
 int /*<<< orphan*/  gen_pool_free (void*,void*,int) ; 
 void* gen_pool_virt_to_phys (void*,void*) ; 
 void* of_gen_pool_get (struct device_node*,char*,int) ; 
 void* sram_resume_address (struct ti_emif_data*,unsigned long) ; 
 void* sram_suspend_address (struct ti_emif_data*,unsigned long) ; 
 scalar_t__ ti_emif_abort_sr ; 
 scalar_t__ ti_emif_enter_sr ; 
 scalar_t__ ti_emif_exit_sr ; 
 scalar_t__ ti_emif_restore_context ; 
 scalar_t__ ti_emif_run_hw_leveling ; 
 scalar_t__ ti_emif_save_context ; 
 int ti_emif_sram_sz ; 

__attribute__((used)) static int ti_emif_alloc_sram(struct device *dev,
			      struct ti_emif_data *emif_data)
{
	struct device_node *np = dev->of_node;
	int ret;

	emif_data->sram_pool_code = of_gen_pool_get(np, "sram", 0);
	if (!emif_data->sram_pool_code) {
		dev_err(dev, "Unable to get sram pool for ocmcram code\n");
		return -ENODEV;
	}

	emif_data->ti_emif_sram_virt =
			gen_pool_alloc(emif_data->sram_pool_code,
				       ti_emif_sram_sz);
	if (!emif_data->ti_emif_sram_virt) {
		dev_err(dev, "Unable to allocate code memory from ocmcram\n");
		return -ENOMEM;
	}

	/* Save physical address to calculate resume offset during pm init */
	emif_data->ti_emif_sram_phys =
			gen_pool_virt_to_phys(emif_data->sram_pool_code,
					      emif_data->ti_emif_sram_virt);

	/* Get sram pool for data section and allocate space */
	emif_data->sram_pool_data = of_gen_pool_get(np, "sram", 1);
	if (!emif_data->sram_pool_data) {
		dev_err(dev, "Unable to get sram pool for ocmcram data\n");
		ret = -ENODEV;
		goto err_free_sram_code;
	}

	emif_data->ti_emif_sram_data_virt =
				gen_pool_alloc(emif_data->sram_pool_data,
					       sizeof(struct emif_regs_amx3));
	if (!emif_data->ti_emif_sram_data_virt) {
		dev_err(dev, "Unable to allocate data memory from ocmcram\n");
		ret = -ENOMEM;
		goto err_free_sram_code;
	}

	/* Save physical address to calculate resume offset during pm init */
	emif_data->ti_emif_sram_data_phys =
		gen_pool_virt_to_phys(emif_data->sram_pool_data,
				      emif_data->ti_emif_sram_data_virt);
	/*
	 * These functions are called during suspend path while MMU is
	 * still on so add virtual base to offset for absolute address
	 */
	emif_data->pm_functions.save_context =
		sram_suspend_address(emif_data,
				     (unsigned long)ti_emif_save_context);
	emif_data->pm_functions.enter_sr =
		sram_suspend_address(emif_data,
				     (unsigned long)ti_emif_enter_sr);
	emif_data->pm_functions.abort_sr =
		sram_suspend_address(emif_data,
				     (unsigned long)ti_emif_abort_sr);

	/*
	 * These are called during resume path when MMU is not enabled
	 * so physical address is used instead
	 */
	emif_data->pm_functions.restore_context =
		sram_resume_address(emif_data,
				    (unsigned long)ti_emif_restore_context);
	emif_data->pm_functions.exit_sr =
		sram_resume_address(emif_data,
				    (unsigned long)ti_emif_exit_sr);
	emif_data->pm_functions.run_hw_leveling =
		sram_resume_address(emif_data,
				    (unsigned long)ti_emif_run_hw_leveling);

	emif_data->pm_data.regs_virt =
		(struct emif_regs_amx3 *)emif_data->ti_emif_sram_data_virt;
	emif_data->pm_data.regs_phys = emif_data->ti_emif_sram_data_phys;

	return 0;

err_free_sram_code:
	gen_pool_free(emif_data->sram_pool_code, emif_data->ti_emif_sram_virt,
		      ti_emif_sram_sz);
	return ret;
}