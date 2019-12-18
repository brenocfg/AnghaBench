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
typedef  scalar_t__ u64 ;
struct tmc_sg_table {int dummy; } ;
struct etr_buf {scalar_t__ hwaddr; scalar_t__ len; scalar_t__ offset; scalar_t__ size; int /*<<< orphan*/  full; struct catu_etr_buf* private; } ;
struct catu_etr_buf {struct tmc_sg_table* catu_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  tmc_sg_table_sync_data_range (struct tmc_sg_table*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void catu_sync_etr_buf(struct etr_buf *etr_buf, u64 rrp, u64 rwp)
{
	struct catu_etr_buf *catu_buf = etr_buf->private;
	struct tmc_sg_table *catu_table = catu_buf->catu_table;
	u64 r_offset, w_offset;

	/*
	 * ETR started off at etr_buf->hwaddr. Convert the RRP/RWP to
	 * offsets within the trace buffer.
	 */
	r_offset = rrp - etr_buf->hwaddr;
	w_offset = rwp - etr_buf->hwaddr;

	if (!etr_buf->full) {
		etr_buf->len = w_offset - r_offset;
		if (w_offset < r_offset)
			etr_buf->len += etr_buf->size;
	} else {
		etr_buf->len = etr_buf->size;
	}

	etr_buf->offset = r_offset;
	tmc_sg_table_sync_data_range(catu_table, r_offset, etr_buf->len);
}