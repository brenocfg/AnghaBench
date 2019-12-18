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
typedef  int u32 ;
struct block_header {int /*<<< orphan*/ * input_ids; int /*<<< orphan*/  pipeline_info; } ;

/* Variables and functions */
 int BIT (int) ; 
 int PIPELINE_INFO_N_VALID_INPUTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_resources_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static u32 get_valid_inputs(struct block_header *blk)
{
	u32 valid_inputs = 0, comp_id;
	int i;

	for (i = 0; i < PIPELINE_INFO_N_VALID_INPUTS(blk->pipeline_info); i++) {
		get_resources_id(blk->input_ids[i], NULL, &comp_id);
		if (comp_id == 0xFFFFFFFF)
			continue;
		valid_inputs |= BIT(comp_id);
	}

	return valid_inputs;
}