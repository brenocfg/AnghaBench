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
typedef  int /*<<< orphan*/  slidx_list_t ;
typedef  int /*<<< orphan*/  sal_processor_static_info_t ;
typedef  int /*<<< orphan*/  sal_log_smbios_dev_err_info_t ;
typedef  int /*<<< orphan*/  sal_log_sel_dev_err_info_t ;
typedef  int /*<<< orphan*/  sal_log_processor_info_t ;
typedef  int /*<<< orphan*/  sal_log_plat_specific_err_info_t ;
typedef  int /*<<< orphan*/  sal_log_plat_bus_err_info_t ;
typedef  int /*<<< orphan*/  sal_log_pci_comp_err_info_t ;
typedef  int /*<<< orphan*/  sal_log_pci_bus_err_info_t ;
typedef  int /*<<< orphan*/  sal_log_mem_dev_err_info_t ;
typedef  int /*<<< orphan*/  sal_log_host_ctlr_err_info_t ;
struct TYPE_2__ {int max_idx; scalar_t__ buffer; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int sal_rec_max ; 
 TYPE_1__ slidx_pool ; 

__attribute__((used)) static int
init_record_index_pools(void)
{
	int i;
	int rec_max_size;  /* Maximum size of SAL error records */
	int sect_min_size; /* Minimum size of SAL error sections */
	/* minimum size table of each section */
	static int sal_log_sect_min_sizes[] = {
		sizeof(sal_log_processor_info_t)
		+ sizeof(sal_processor_static_info_t),
		sizeof(sal_log_mem_dev_err_info_t),
		sizeof(sal_log_sel_dev_err_info_t),
		sizeof(sal_log_pci_bus_err_info_t),
		sizeof(sal_log_smbios_dev_err_info_t),
		sizeof(sal_log_pci_comp_err_info_t),
		sizeof(sal_log_plat_specific_err_info_t),
		sizeof(sal_log_host_ctlr_err_info_t),
		sizeof(sal_log_plat_bus_err_info_t),
	};

	/*
	 * MCA handler cannot allocate new memory on flight,
	 * so we preallocate enough memory to handle a SAL record.
	 *
	 * Initialize a handling set of slidx_pool:
	 *   1. Pick up the max size of SAL error records
	 *   2. Pick up the min size of SAL error sections
	 *   3. Allocate the pool as enough to 2 SAL records
	 *     (now we can estimate the maxinum of section in a record.)
	 */

	/* - 1 - */
	rec_max_size = sal_rec_max;

	/* - 2 - */
	sect_min_size = sal_log_sect_min_sizes[0];
	for (i = 1; i < sizeof sal_log_sect_min_sizes/sizeof(size_t); i++)
		if (sect_min_size > sal_log_sect_min_sizes[i])
			sect_min_size = sal_log_sect_min_sizes[i];

	/* - 3 - */
	slidx_pool.max_idx = (rec_max_size/sect_min_size) * 2 + 1;
	slidx_pool.buffer =
		kmalloc_array(slidx_pool.max_idx, sizeof(slidx_list_t),
			      GFP_KERNEL);

	return slidx_pool.buffer ? 0 : -ENOMEM;
}