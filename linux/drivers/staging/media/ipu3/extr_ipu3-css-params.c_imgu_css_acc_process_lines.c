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
struct process_lines {unsigned short y_start; unsigned short grid_height; unsigned short block_height; unsigned short grid_height_per_slice; unsigned short const image_height; unsigned short max_op; unsigned short max_tr; scalar_t__ acc_enable; } ;
struct imgu_abi_acc_transfer_op_data {unsigned char set_number; } ;
struct imgu_abi_acc_process_lines_cmd_data {unsigned short lines; unsigned char cfg_set; } ;
struct imgu_abi_acc_operation {void* op_indicator; int /*<<< orphan*/  op_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IMGU_ABI_ACC_OPTYPE_PROCESS_LINES ; 
 int /*<<< orphan*/  IMGU_ABI_ACC_OPTYPE_TRANSFER_DATA ; 
 void* IMGU_ABI_ACC_OP_END_OF_ACK ; 
 void* IMGU_ABI_ACC_OP_END_OF_OPS ; 
 void* IMGU_ABI_ACC_OP_IDLE ; 
 unsigned short IMGU_ABI_AF_MAX_OPERATIONS ; 

__attribute__((used)) static int
imgu_css_acc_process_lines(const struct process_lines *pl,
			   struct imgu_abi_acc_operation *p_op,
			   struct imgu_abi_acc_process_lines_cmd_data *p_pl,
			   struct imgu_abi_acc_transfer_op_data *p_tr)
{
	unsigned short op_idx = 0, pl_idx = 0, tr_idx = 0;
	unsigned char tr_set_num = 0, pl_cfg_set = 0;
	const unsigned short grid_last_line =
			pl->y_start + pl->grid_height * pl->block_height;
	const unsigned short process_lines =
			pl->grid_height_per_slice * pl->block_height;

	unsigned int process_lines_after_grid;
	unsigned short first_process_lines;
	unsigned short last_process_lines_in_grid;

	unsigned short num_of_process_lines;
	unsigned short num_of_sets;

	if (pl->grid_height_per_slice == 0)
		return -EINVAL;

	if (pl->acc_enable && grid_last_line > pl->image_height)
		return -EINVAL;

	num_of_sets = pl->grid_height / pl->grid_height_per_slice;
	if (num_of_sets * pl->grid_height_per_slice < pl->grid_height)
		num_of_sets++;

	/* Account for two line delay inside the FF */
	if (pl->max_op == IMGU_ABI_AF_MAX_OPERATIONS) {
		first_process_lines = process_lines + pl->y_start + 2;
		last_process_lines_in_grid =
			(grid_last_line - first_process_lines) -
			((num_of_sets - 2) * process_lines) + 4;
		process_lines_after_grid =
			pl->image_height - grid_last_line - 4;
	} else {
		first_process_lines = process_lines + pl->y_start;
		last_process_lines_in_grid =
			(grid_last_line - first_process_lines) -
			((num_of_sets - 2) * process_lines);
		process_lines_after_grid = pl->image_height - grid_last_line;
	}

	num_of_process_lines = num_of_sets;
	if (process_lines_after_grid > 0)
		num_of_process_lines++;

	while (tr_idx < num_of_sets || pl_idx < num_of_process_lines) {
		/* Read meta-data */
		if (pl_idx >= 2 || (pl_idx == 1 && num_of_sets == 1)) {
			if (op_idx >= pl->max_op || tr_idx >= pl->max_tr)
				return -EINVAL;

			p_op[op_idx].op_type =
				IMGU_ABI_ACC_OPTYPE_TRANSFER_DATA;

			if (tr_idx == num_of_sets - 1)
				/* The last operation is always a tr */
				p_op[op_idx].op_indicator =
					IMGU_ABI_ACC_OP_END_OF_OPS;
			else if (tr_idx == num_of_sets - 2)
				if (process_lines_after_grid == 0)
					/*
					 * No additional pl op left -
					 * this op is left as lats of cycle
					 */
					p_op[op_idx].op_indicator =
						IMGU_ABI_ACC_OP_END_OF_ACK;
				else
					/*
					 * We still have to process-lines after
					 * the grid so have one more pl op
					 */
					p_op[op_idx].op_indicator =
						IMGU_ABI_ACC_OP_IDLE;
			else
				/* Default - usually there's a pl after a tr */
				p_op[op_idx].op_indicator =
					IMGU_ABI_ACC_OP_IDLE;

			op_idx++;
			if (p_tr) {
				p_tr[tr_idx].set_number = tr_set_num;
				tr_set_num = 1 - tr_set_num;
			}
			tr_idx++;
		}

		/* process_lines */
		if (pl_idx < num_of_process_lines) {
			if (op_idx >= pl->max_op || pl_idx >= pl->max_tr)
				return -EINVAL;

			p_op[op_idx].op_type =
				IMGU_ABI_ACC_OPTYPE_PROCESS_LINES;
			if (pl_idx == 0)
				if (num_of_process_lines == 1)
					/* Only one pl op */
					p_op[op_idx].op_indicator =
						IMGU_ABI_ACC_OP_END_OF_ACK;
				else
					/* On init - do two pl ops */
					p_op[op_idx].op_indicator =
						IMGU_ABI_ACC_OP_IDLE;
			else
				/* Usually pl is the end of the ack cycle */
				p_op[op_idx].op_indicator =
					IMGU_ABI_ACC_OP_END_OF_ACK;

			op_idx++;

			if (pl_idx == 0)
				/* First process line */
				p_pl[pl_idx].lines = first_process_lines;
			else if (pl_idx == num_of_sets - 1)
				/* Last in grid */
				p_pl[pl_idx].lines = last_process_lines_in_grid;
			else if (pl_idx == num_of_process_lines - 1)
				/* After the grid */
				p_pl[pl_idx].lines = process_lines_after_grid;
			else
				/* Inside the grid */
				p_pl[pl_idx].lines = process_lines;

			if (p_tr) {
				p_pl[pl_idx].cfg_set = pl_cfg_set;
				pl_cfg_set = 1 - pl_cfg_set;
			}
			pl_idx++;
		}
	}

	return 0;
}