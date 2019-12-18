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
struct dcn_hubbub_virt_addr_config {int /*<<< orphan*/  page_table_base_addr; int /*<<< orphan*/  page_table_depth; int /*<<< orphan*/  page_table_block_size; int /*<<< orphan*/  page_table_end_addr; int /*<<< orphan*/  page_table_start_addr; } ;
struct dce_hwseq {int dummy; } ;
struct dc_virtual_addr_space_config {int /*<<< orphan*/  page_table_base_addr; int /*<<< orphan*/  page_table_depth; int /*<<< orphan*/  page_table_block_size_in_bytes; int /*<<< orphan*/  page_table_end_addr; int /*<<< orphan*/  page_table_start_addr; } ;
struct dc {TYPE_2__* res_pool; } ;
struct TYPE_6__ {TYPE_1__* funcs; } ;
struct TYPE_5__ {TYPE_3__* hubbub; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* init_vm_ctx ) (TYPE_3__*,struct dcn_hubbub_virt_addr_config*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct dcn_hubbub_virt_addr_config*,int) ; 

__attribute__((used)) static void dcn20_init_vm_ctx(
		struct dce_hwseq *hws,
		struct dc *dc,
		struct dc_virtual_addr_space_config *va_config,
		int vmid)
{
	struct dcn_hubbub_virt_addr_config config;

	if (vmid == 0) {
		ASSERT(0); /* VMID cannot be 0 for vm context */
		return;
	}

	config.page_table_start_addr = va_config->page_table_start_addr;
	config.page_table_end_addr = va_config->page_table_end_addr;
	config.page_table_block_size = va_config->page_table_block_size_in_bytes;
	config.page_table_depth = va_config->page_table_depth;
	config.page_table_base_addr = va_config->page_table_base_addr;

	dc->res_pool->hubbub->funcs->init_vm_ctx(dc->res_pool->hubbub, &config, vmid);
}