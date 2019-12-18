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
struct asic_fixed_properties {int mmu_pgt_size; scalar_t__ pcie_aux_dbi_reg_addr; int /*<<< orphan*/  pcie_dbi_base_address; int /*<<< orphan*/  tpc_enabled_mask; int /*<<< orphan*/  max_power_default; int /*<<< orphan*/  cb_pool_cb_size; int /*<<< orphan*/  cb_pool_cb_cnt; int /*<<< orphan*/  high_pll; int /*<<< orphan*/  num_of_events; int /*<<< orphan*/  max_asid; int /*<<< orphan*/  cfg_size; int /*<<< orphan*/  va_space_dram_end_address; int /*<<< orphan*/  dram_size_for_default_page_mapping; int /*<<< orphan*/  va_space_dram_start_address; int /*<<< orphan*/  va_space_host_end_address; int /*<<< orphan*/  va_space_host_start_address; int /*<<< orphan*/  dram_page_size; int /*<<< orphan*/  mmu_hop0_tables_total_size; int /*<<< orphan*/  mmu_hop_table_size; int /*<<< orphan*/  mmu_pte_size; int /*<<< orphan*/  mmu_dram_default_page_addr; int /*<<< orphan*/  mmu_pgt_addr; scalar_t__ sram_base_address; scalar_t__ sram_user_base_address; scalar_t__ sram_size; scalar_t__ sram_end_address; int /*<<< orphan*/  dram_user_base_address; scalar_t__ dram_size; scalar_t__ dram_base_address; scalar_t__ dram_end_address; int /*<<< orphan*/  completion_queues_count; TYPE_1__* hw_queues_props; } ;
struct hl_device {scalar_t__ pldm; struct asic_fixed_properties asic_prop; } ;
struct TYPE_2__ {int driver_only; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ CFG_BASE ; 
 int /*<<< orphan*/  CFG_SIZE ; 
 int /*<<< orphan*/  DRAM_BASE_ADDR_USER ; 
 scalar_t__ DRAM_PHYS_BASE ; 
 scalar_t__ DRAM_PHYS_DEFAULT_SIZE ; 
 int /*<<< orphan*/  GOYA_ASYNC_EVENT_ID_SIZE ; 
 int /*<<< orphan*/  GOYA_CB_POOL_CB_CNT ; 
 int /*<<< orphan*/  GOYA_CB_POOL_CB_SIZE ; 
 int HL_MAX_QUEUES ; 
 int /*<<< orphan*/  HL_PTE_SIZE ; 
 int /*<<< orphan*/  HOP0_TABLES_TOTAL_SIZE ; 
 int /*<<< orphan*/  HOP_TABLE_SIZE ; 
 int /*<<< orphan*/  MAX_ASID ; 
 int /*<<< orphan*/  MAX_POWER_DEFAULT ; 
 int /*<<< orphan*/  MMU_DRAM_DEFAULT_PAGE_ADDR ; 
 int /*<<< orphan*/  MMU_PAGE_TABLES_ADDR ; 
 int MMU_PAGE_TABLES_SIZE ; 
 int /*<<< orphan*/  NUMBER_OF_CMPLT_QUEUES ; 
 int NUMBER_OF_CPU_HW_QUEUES ; 
 int NUMBER_OF_EXT_HW_QUEUES ; 
 int NUMBER_OF_INT_HW_QUEUES ; 
 int /*<<< orphan*/  PAGE_SIZE_2MB ; 
 int /*<<< orphan*/  PLL_HIGH_DEFAULT ; 
 int /*<<< orphan*/  QUEUE_TYPE_CPU ; 
 int /*<<< orphan*/  QUEUE_TYPE_EXT ; 
 int /*<<< orphan*/  QUEUE_TYPE_INT ; 
 int /*<<< orphan*/  QUEUE_TYPE_NA ; 
 scalar_t__ SRAM_BASE_ADDR ; 
 scalar_t__ SRAM_SIZE ; 
 scalar_t__ SRAM_USER_BASE_OFFSET ; 
 int /*<<< orphan*/  TPC_ENABLED_MASK ; 
 int /*<<< orphan*/  VA_DDR_SPACE_END ; 
 int /*<<< orphan*/  VA_DDR_SPACE_START ; 
 int /*<<< orphan*/  VA_HOST_SPACE_END ; 
 int /*<<< orphan*/  VA_HOST_SPACE_START ; 
 scalar_t__ mmPCIE_AUX_DBI ; 
 int /*<<< orphan*/  mmPCIE_DBI_BASE ; 

void goya_get_fixed_properties(struct hl_device *hdev)
{
	struct asic_fixed_properties *prop = &hdev->asic_prop;
	int i;

	for (i = 0 ; i < NUMBER_OF_EXT_HW_QUEUES ; i++) {
		prop->hw_queues_props[i].type = QUEUE_TYPE_EXT;
		prop->hw_queues_props[i].driver_only = 0;
	}

	for (; i < NUMBER_OF_EXT_HW_QUEUES + NUMBER_OF_CPU_HW_QUEUES ; i++) {
		prop->hw_queues_props[i].type = QUEUE_TYPE_CPU;
		prop->hw_queues_props[i].driver_only = 1;
	}

	for (; i < NUMBER_OF_EXT_HW_QUEUES + NUMBER_OF_CPU_HW_QUEUES +
			NUMBER_OF_INT_HW_QUEUES; i++) {
		prop->hw_queues_props[i].type = QUEUE_TYPE_INT;
		prop->hw_queues_props[i].driver_only = 0;
	}

	for (; i < HL_MAX_QUEUES; i++)
		prop->hw_queues_props[i].type = QUEUE_TYPE_NA;

	prop->completion_queues_count = NUMBER_OF_CMPLT_QUEUES;

	prop->dram_base_address = DRAM_PHYS_BASE;
	prop->dram_size = DRAM_PHYS_DEFAULT_SIZE;
	prop->dram_end_address = prop->dram_base_address + prop->dram_size;
	prop->dram_user_base_address = DRAM_BASE_ADDR_USER;

	prop->sram_base_address = SRAM_BASE_ADDR;
	prop->sram_size = SRAM_SIZE;
	prop->sram_end_address = prop->sram_base_address + prop->sram_size;
	prop->sram_user_base_address = prop->sram_base_address +
						SRAM_USER_BASE_OFFSET;

	prop->mmu_pgt_addr = MMU_PAGE_TABLES_ADDR;
	prop->mmu_dram_default_page_addr = MMU_DRAM_DEFAULT_PAGE_ADDR;
	if (hdev->pldm)
		prop->mmu_pgt_size = 0x800000; /* 8MB */
	else
		prop->mmu_pgt_size = MMU_PAGE_TABLES_SIZE;
	prop->mmu_pte_size = HL_PTE_SIZE;
	prop->mmu_hop_table_size = HOP_TABLE_SIZE;
	prop->mmu_hop0_tables_total_size = HOP0_TABLES_TOTAL_SIZE;
	prop->dram_page_size = PAGE_SIZE_2MB;

	prop->va_space_host_start_address = VA_HOST_SPACE_START;
	prop->va_space_host_end_address = VA_HOST_SPACE_END;
	prop->va_space_dram_start_address = VA_DDR_SPACE_START;
	prop->va_space_dram_end_address = VA_DDR_SPACE_END;
	prop->dram_size_for_default_page_mapping =
			prop->va_space_dram_end_address;
	prop->cfg_size = CFG_SIZE;
	prop->max_asid = MAX_ASID;
	prop->num_of_events = GOYA_ASYNC_EVENT_ID_SIZE;
	prop->high_pll = PLL_HIGH_DEFAULT;
	prop->cb_pool_cb_cnt = GOYA_CB_POOL_CB_CNT;
	prop->cb_pool_cb_size = GOYA_CB_POOL_CB_SIZE;
	prop->max_power_default = MAX_POWER_DEFAULT;
	prop->tpc_enabled_mask = TPC_ENABLED_MASK;
	prop->pcie_dbi_base_address = mmPCIE_DBI_BASE;
	prop->pcie_aux_dbi_reg_addr = CFG_BASE + mmPCIE_AUX_DBI;
}