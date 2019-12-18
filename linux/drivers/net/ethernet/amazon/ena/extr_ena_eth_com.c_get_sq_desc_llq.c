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
typedef  int /*<<< orphan*/  u8 ;
struct ena_com_llq_pkt_ctrl {int idx; int /*<<< orphan*/  descs_left_in_line; int /*<<< orphan*/ * curr_bounce_buf; } ;
struct ena_com_io_sq {int desc_entry_size; struct ena_com_llq_pkt_ctrl llq_buf_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void *get_sq_desc_llq(struct ena_com_io_sq *io_sq)
{
	struct ena_com_llq_pkt_ctrl *pkt_ctrl = &io_sq->llq_buf_ctrl;
	u8 *bounce_buffer;
	void *sq_desc;

	bounce_buffer = pkt_ctrl->curr_bounce_buf;

	if (unlikely(!bounce_buffer)) {
		pr_err("bounce buffer is NULL\n");
		return NULL;
	}

	sq_desc = bounce_buffer + pkt_ctrl->idx * io_sq->desc_entry_size;
	pkt_ctrl->idx++;
	pkt_ctrl->descs_left_in_line--;

	return sq_desc;
}