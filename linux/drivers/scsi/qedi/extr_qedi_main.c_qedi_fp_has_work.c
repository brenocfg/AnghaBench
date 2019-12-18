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
typedef  int u16 ;
struct status_block_e4 {int* pi_array; } ;
struct qedi_fastpath {size_t sb_id; struct qed_sb_info* sb_info; struct qedi_ctx* qedi; } ;
struct qedi_ctx {struct global_queue** global_queues; } ;
struct qed_sb_info {struct status_block_e4* sb_virt; } ;
struct global_queue {int cq_cons_idx; } ;

/* Variables and functions */
 int QEDI_CQ_SIZE ; 
 size_t QEDI_PROTO_CQ_PROD_IDX ; 
 int /*<<< orphan*/  barrier () ; 

__attribute__((used)) static bool qedi_fp_has_work(struct qedi_fastpath *fp)
{
	struct qedi_ctx *qedi = fp->qedi;
	struct global_queue *que;
	struct qed_sb_info *sb_info = fp->sb_info;
	struct status_block_e4 *sb = sb_info->sb_virt;
	u16 prod_idx;

	barrier();

	/* Get the current firmware producer index */
	prod_idx = sb->pi_array[QEDI_PROTO_CQ_PROD_IDX];

	/* Get the pointer to the global CQ this completion is on */
	que = qedi->global_queues[fp->sb_id];

	/* prod idx wrap around uint16 */
	if (prod_idx >= QEDI_CQ_SIZE)
		prod_idx = prod_idx % QEDI_CQ_SIZE;

	return (que->cq_cons_idx != prod_idx);
}