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
struct rmi_function_descriptor {int /*<<< orphan*/  function_version; int /*<<< orphan*/  interrupt_source_count; int /*<<< orphan*/  function_number; scalar_t__ data_base_addr; scalar_t__ control_base_addr; scalar_t__ command_base_addr; scalar_t__ query_base_addr; } ;
struct pdt_entry {int /*<<< orphan*/  function_version; int /*<<< orphan*/  interrupt_source_count; int /*<<< orphan*/  function_number; scalar_t__ page_start; scalar_t__ data_base_addr; scalar_t__ control_base_addr; scalar_t__ command_base_addr; scalar_t__ query_base_addr; } ;

/* Variables and functions */

__attribute__((used)) static void rmi_driver_copy_pdt_to_fd(const struct pdt_entry *pdt,
				      struct rmi_function_descriptor *fd)
{
	fd->query_base_addr = pdt->query_base_addr + pdt->page_start;
	fd->command_base_addr = pdt->command_base_addr + pdt->page_start;
	fd->control_base_addr = pdt->control_base_addr + pdt->page_start;
	fd->data_base_addr = pdt->data_base_addr + pdt->page_start;
	fd->function_number = pdt->function_number;
	fd->interrupt_source_count = pdt->interrupt_source_count;
	fd->function_version = pdt->function_version;
}