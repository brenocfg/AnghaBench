#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct process_lines {int block_height; int /*<<< orphan*/  acc_enable; int /*<<< orphan*/  max_tr; int /*<<< orphan*/  max_op; int /*<<< orphan*/  grid_height_per_slice; int /*<<< orphan*/  y_start; int /*<<< orphan*/  grid_height; int /*<<< orphan*/  image_height; } ;
struct TYPE_18__ {int /*<<< orphan*/  awb_acc; } ;
struct TYPE_19__ {TYPE_7__ enable; } ;
struct TYPE_20__ {TYPE_8__ sp; } ;
struct TYPE_11__ {TYPE_9__ isp; } ;
struct imgu_fw_info {TYPE_10__ info; } ;
struct imgu_css_pipe {size_t bindex; TYPE_2__* rect; } ;
struct imgu_css {TYPE_1__* fwp; struct imgu_css_pipe* pipes; } ;
struct imgu_abi_awb_intra_frame_operations_data {int /*<<< orphan*/  transfer_data; int /*<<< orphan*/  process_lines_data; int /*<<< orphan*/  ops; } ;
struct TYPE_14__ {int block_height_log2; int /*<<< orphan*/  y_start; int /*<<< orphan*/  height; } ;
struct TYPE_15__ {TYPE_3__ grid; } ;
struct imgu_abi_awb_config {TYPE_6__* stripes; TYPE_4__ config; struct imgu_abi_awb_intra_frame_operations_data operations_data; } ;
struct TYPE_16__ {int /*<<< orphan*/  height_per_slice; } ;
struct TYPE_17__ {TYPE_5__ grid; } ;
struct TYPE_13__ {int /*<<< orphan*/  height; } ;
struct TYPE_12__ {struct imgu_fw_info* binary_header; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMGU_ABI_AWB_MAX_OPERATIONS ; 
 int /*<<< orphan*/  IMGU_ABI_AWB_MAX_TRANSFERS ; 
 size_t IPU3_CSS_RECT_BDS ; 
 int imgu_css_acc_process_lines (struct process_lines*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imgu_css_awb_ops_calc(struct imgu_css *css, unsigned int pipe,
				 struct imgu_abi_awb_config *awb_config)
{
	struct imgu_abi_awb_intra_frame_operations_data *to =
		&awb_config->operations_data;
	struct imgu_css_pipe *css_pipe = &css->pipes[pipe];
	struct imgu_fw_info *bi =
		&css->fwp->binary_header[css_pipe->bindex];

	struct process_lines pl = {
		.image_height = css_pipe->rect[IPU3_CSS_RECT_BDS].height,
		.grid_height = awb_config->config.grid.height,
		.block_height =
			1 << awb_config->config.grid.block_height_log2,
		.y_start = awb_config->config.grid.y_start,
		.grid_height_per_slice =
			awb_config->stripes[0].grid.height_per_slice,
		.max_op = IMGU_ABI_AWB_MAX_OPERATIONS,
		.max_tr = IMGU_ABI_AWB_MAX_TRANSFERS,
		.acc_enable = bi->info.isp.sp.enable.awb_acc,
	};

	return imgu_css_acc_process_lines(&pl, to->ops, to->process_lines_data,
					  to->transfer_data);
}