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
typedef  scalar_t__ u16 ;
struct ena_com_tx_ctx {scalar_t__ num_bufs; } ;
struct ena_com_llq_info {scalar_t__ descs_num_before_header; int /*<<< orphan*/  descs_per_entry; } ;
struct ena_com_io_sq {int entries_in_tx_burst_left; int /*<<< orphan*/  qid; struct ena_com_llq_info llq_info; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_com_meta_desc_changed (struct ena_com_io_sq*,struct ena_com_tx_ctx*) ; 
 int /*<<< orphan*/  is_llq_max_tx_burst_exists (struct ena_com_io_sq*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool ena_com_is_doorbell_needed(struct ena_com_io_sq *io_sq,
					      struct ena_com_tx_ctx *ena_tx_ctx)
{
	struct ena_com_llq_info *llq_info;
	int descs_after_first_entry;
	int num_entries_needed = 1;
	u16 num_descs;

	if (!is_llq_max_tx_burst_exists(io_sq))
		return false;

	llq_info = &io_sq->llq_info;
	num_descs = ena_tx_ctx->num_bufs;

	if (unlikely(ena_com_meta_desc_changed(io_sq, ena_tx_ctx)))
		++num_descs;

	if (num_descs > llq_info->descs_num_before_header) {
		descs_after_first_entry = num_descs - llq_info->descs_num_before_header;
		num_entries_needed += DIV_ROUND_UP(descs_after_first_entry,
						   llq_info->descs_per_entry);
	}

	pr_debug("queue: %d num_descs: %d num_entries_needed: %d\n", io_sq->qid,
		 num_descs, num_entries_needed);

	return num_entries_needed > io_sq->entries_in_tx_burst_left;
}