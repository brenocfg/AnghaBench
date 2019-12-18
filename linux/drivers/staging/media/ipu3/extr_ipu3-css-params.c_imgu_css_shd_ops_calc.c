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
struct ipu3_uapi_shd_grid_config {int block_height_log2; unsigned int grid_height_per_slice; scalar_t__ y_start; } ;
struct imgu_abi_shd_transfer_luts_set_data {unsigned char set_number; } ;
struct imgu_abi_shd_intra_frame_operations_data {struct imgu_abi_shd_transfer_luts_set_data* transfer_data; struct imgu_abi_acc_process_lines_cmd_data* process_lines_data; struct imgu_abi_acc_operation* operation_list; } ;
struct imgu_abi_acc_process_lines_cmd_data {unsigned int lines; unsigned char cfg_set; } ;
struct imgu_abi_acc_operation {void* op_indicator; int /*<<< orphan*/  op_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IMGU_ABI_ACC_OPTYPE_PROCESS_LINES ; 
 int /*<<< orphan*/  IMGU_ABI_ACC_OPTYPE_TRANSFER_DATA ; 
 void* IMGU_ABI_ACC_OP_END_OF_ACK ; 
 void* IMGU_ABI_ACC_OP_END_OF_OPS ; 
 void* IMGU_ABI_ACC_OP_IDLE ; 
 unsigned int IMGU_ABI_SHD_MAX_OPERATIONS ; 
 unsigned int IMGU_ABI_SHD_MAX_PROCESS_LINES ; 
 unsigned int IMGU_ABI_SHD_MAX_TRANSFERS ; 
 unsigned char IMGU_SHD_SETS ; 
 int /*<<< orphan*/  memset (struct imgu_abi_shd_intra_frame_operations_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
imgu_css_shd_ops_calc(struct imgu_abi_shd_intra_frame_operations_data *ops,
		      const struct ipu3_uapi_shd_grid_config *grid,
		      unsigned int image_height)
{
	unsigned int block_height = 1 << grid->block_height_log2;
	unsigned int grid_height_per_slice = grid->grid_height_per_slice;
	unsigned int set_height = grid_height_per_slice * block_height;

	/* We currently support only abs(y_start) > grid_height_per_slice */
	unsigned int positive_y_start = (unsigned int)-grid->y_start;
	unsigned int first_process_lines =
				set_height - (positive_y_start % set_height);
	unsigned int last_set_height;
	unsigned int num_of_sets;

	struct imgu_abi_acc_operation *p_op;
	struct imgu_abi_acc_process_lines_cmd_data *p_pl;
	struct imgu_abi_shd_transfer_luts_set_data *p_tr;

	unsigned int op_idx, pl_idx, tr_idx;
	unsigned char tr_set_num, pl_cfg_set;

	/*
	 * When the number of lines for the last process lines command
	 * is equal to a set height, we need another line of grid cell -
	 * additional transfer is required.
	 */
	unsigned char last_tr = 0;

	/* Add "process lines" command to the list of operations */
	bool add_pl;
	/* Add DMA xfer (config set) command to the list of ops */
	bool add_tr;

	/*
	 * Available partial grid (the part that fits into #IMGU_SHD_SETS sets)
	 * doesn't cover whole frame - need to process in chunks
	 */
	if (image_height > first_process_lines) {
		last_set_height =
			(image_height - first_process_lines) % set_height;
		num_of_sets = last_set_height > 0 ?
			(image_height - first_process_lines) / set_height + 2 :
			(image_height - first_process_lines) / set_height + 1;
		last_tr = (set_height - last_set_height <= block_height ||
			   last_set_height == 0) ? 1 : 0;
	} else { /* partial grid covers whole frame */
		last_set_height = 0;
		num_of_sets = 1;
		first_process_lines = image_height;
		last_tr = set_height - image_height <= block_height ? 1 : 0;
	}

	/* Init operations lists and counters */
	p_op = ops->operation_list;
	op_idx = 0;
	p_pl = ops->process_lines_data;
	pl_idx = 0;
	p_tr = ops->transfer_data;
	tr_idx = 0;

	memset(ops, 0, sizeof(*ops));

	/* Cyclic counters that holds config set number [0,IMGU_SHD_SETS) */
	tr_set_num = 0;
	pl_cfg_set = 0;

	/*
	 * Always start with a transfer - process lines command must be
	 * initiated only after appropriate config sets are in place
	 * (2 configuration sets per process line command, except for last one).
	 */
	add_pl = false;
	add_tr = true;

	while (add_pl || add_tr) {
		/* Transfer ops */
		if (add_tr) {
			if (op_idx >= IMGU_ABI_SHD_MAX_OPERATIONS ||
			    tr_idx >= IMGU_ABI_SHD_MAX_TRANSFERS)
				return -EINVAL;
			p_op[op_idx].op_type =
				IMGU_ABI_ACC_OPTYPE_TRANSFER_DATA;
			p_op[op_idx].op_indicator = IMGU_ABI_ACC_OP_IDLE;
			op_idx++;
			p_tr[tr_idx].set_number = tr_set_num;
			tr_idx++;
			tr_set_num = (tr_set_num + 1) % IMGU_SHD_SETS;
		}

		/* Process-lines ops */
		if (add_pl) {
			if (op_idx >= IMGU_ABI_SHD_MAX_OPERATIONS ||
			    pl_idx >= IMGU_ABI_SHD_MAX_PROCESS_LINES)
				return -EINVAL;
			p_op[op_idx].op_type =
				IMGU_ABI_ACC_OPTYPE_PROCESS_LINES;

			/*
			 * In case we have 2 process lines commands -
			 * don't stop after the first one
			 */
			if (pl_idx == 0 && num_of_sets != 1)
				p_op[op_idx].op_indicator =
					IMGU_ABI_ACC_OP_IDLE;
			/*
			 * Initiate last process lines command -
			 * end of operation list.
			 */
			else if (pl_idx == num_of_sets - 1)
				p_op[op_idx].op_indicator =
					IMGU_ABI_ACC_OP_END_OF_OPS;
			/*
			 * Intermediate process line command - end of operation
			 * "chunk" (meaning few "transfers" followed by few
			 * "process lines" commands).
			 */
			else
				p_op[op_idx].op_indicator =
					IMGU_ABI_ACC_OP_END_OF_ACK;

			op_idx++;

			/* first process line operation */
			if (pl_idx == 0)
				p_pl[pl_idx].lines = first_process_lines;
			/* Last process line operation */
			else if (pl_idx == num_of_sets - 1 &&
				 last_set_height > 0)
				p_pl[pl_idx].lines = last_set_height;
			else	/* "regular" process lines operation */
				p_pl[pl_idx].lines = set_height;

			p_pl[pl_idx].cfg_set = pl_cfg_set;
			pl_idx++;
			pl_cfg_set = (pl_cfg_set + 1) % IMGU_SHD_SETS;
		}

		/*
		 * Initially, we always transfer
		 * min(IMGU_SHD_SETS, num_of_sets) - after that we fill in the
		 * corresponding process lines commands.
		 */
		if (tr_idx == IMGU_SHD_SETS ||
		    tr_idx == num_of_sets + last_tr) {
			add_tr = false;
			add_pl = true;
		}

		/*
		 * We have finished the "initial" operations chunk -
		 * be ready to get more chunks.
		 */
		if (pl_idx == 2) {
			add_tr = true;
			add_pl = true;
		}

		/* Stop conditions for each operation type */
		if (tr_idx == num_of_sets + last_tr)
			add_tr = false;
		if (pl_idx == num_of_sets)
			add_pl = false;
	}

	return 0;
}