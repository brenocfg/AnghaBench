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
struct ena_llq_configurations {int llq_ring_entry_size_value; int /*<<< orphan*/  llq_num_decs_before_header; int /*<<< orphan*/  llq_stride_ctrl; int /*<<< orphan*/  llq_ring_entry_size; int /*<<< orphan*/  llq_header_location; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_ADMIN_INLINE_HEADER ; 
 int /*<<< orphan*/  ENA_ADMIN_LIST_ENTRY_SIZE_128B ; 
 int /*<<< orphan*/  ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_2 ; 
 int /*<<< orphan*/  ENA_ADMIN_MULTIPLE_DESCS_PER_ENTRY ; 

__attribute__((used)) static void set_default_llq_configurations(struct ena_llq_configurations *llq_config)
{
	llq_config->llq_header_location = ENA_ADMIN_INLINE_HEADER;
	llq_config->llq_ring_entry_size = ENA_ADMIN_LIST_ENTRY_SIZE_128B;
	llq_config->llq_stride_ctrl = ENA_ADMIN_MULTIPLE_DESCS_PER_ENTRY;
	llq_config->llq_num_decs_before_header = ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_2;
	llq_config->llq_ring_entry_size_value = 128;
}