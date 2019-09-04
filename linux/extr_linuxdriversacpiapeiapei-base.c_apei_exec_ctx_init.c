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
typedef  void* u32 ;
struct apei_exec_ins_type {int dummy; } ;
struct apei_exec_context {void* entries; struct acpi_whea_header* action_table; void* instructions; struct apei_exec_ins_type* ins_table; } ;
struct acpi_whea_header {int dummy; } ;

/* Variables and functions */

void apei_exec_ctx_init(struct apei_exec_context *ctx,
			struct apei_exec_ins_type *ins_table,
			u32 instructions,
			struct acpi_whea_header *action_table,
			u32 entries)
{
	ctx->ins_table = ins_table;
	ctx->instructions = instructions;
	ctx->action_table = action_table;
	ctx->entries = entries;
}