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
struct ena_com_llq_pkt_ctrl {int /*<<< orphan*/  descs_left_in_line; scalar_t__ idx; int /*<<< orphan*/  curr_bounce_buf; } ;
struct ena_com_llq_info {int /*<<< orphan*/  descs_num_before_header; int /*<<< orphan*/  desc_list_entry_size; } ;
struct ena_com_io_sq {scalar_t__ mem_queue_type; struct ena_com_llq_pkt_ctrl llq_buf_ctrl; int /*<<< orphan*/  bounce_buf_ctrl; struct ena_com_llq_info llq_info; } ;

/* Variables and functions */
 scalar_t__ ENA_ADMIN_PLACEMENT_POLICY_HOST ; 
 int /*<<< orphan*/  ena_com_get_next_bounce_buffer (int /*<<< orphan*/ *) ; 
 int ena_com_write_bounce_buffer_to_dev (struct ena_com_io_sq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ena_com_close_bounce_buffer(struct ena_com_io_sq *io_sq)
{
	struct ena_com_llq_pkt_ctrl *pkt_ctrl = &io_sq->llq_buf_ctrl;
	struct ena_com_llq_info *llq_info = &io_sq->llq_info;
	int rc;

	if (unlikely(io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_HOST))
		return 0;

	/* bounce buffer was used, so write it and get a new one */
	if (pkt_ctrl->idx) {
		rc = ena_com_write_bounce_buffer_to_dev(io_sq,
							pkt_ctrl->curr_bounce_buf);
		if (unlikely(rc))
			return rc;

		pkt_ctrl->curr_bounce_buf =
			ena_com_get_next_bounce_buffer(&io_sq->bounce_buf_ctrl);
		memset(io_sq->llq_buf_ctrl.curr_bounce_buf,
		       0x0, llq_info->desc_list_entry_size);
	}

	pkt_ctrl->idx = 0;
	pkt_ctrl->descs_left_in_line = llq_info->descs_num_before_header;
	return 0;
}