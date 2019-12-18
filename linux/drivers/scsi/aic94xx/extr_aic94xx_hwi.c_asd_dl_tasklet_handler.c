#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct done_list_struct {int toggle; int /*<<< orphan*/  index; } ;
struct asd_seq_data {size_t dl_next; int dl_toggle; int /*<<< orphan*/  pend_q_lock; int /*<<< orphan*/  pending; int /*<<< orphan*/  tc_index_lock; struct done_list_struct* dl; } ;
struct asd_ha_struct {struct asd_seq_data seq; } ;
struct asd_ascb {int /*<<< orphan*/  (* tasklet_complete ) (struct asd_ascb*,struct done_list_struct*) ;int /*<<< orphan*/  list; int /*<<< orphan*/  timer; int /*<<< orphan*/  uldd_timer; TYPE_2__* scb; } ;
struct TYPE_3__ {scalar_t__ opcode; } ;
struct TYPE_4__ {TYPE_1__ header; } ;

/* Variables and functions */
 int ASD_DL_SIZE ; 
 int /*<<< orphan*/  ASD_DPRINTK (char*) ; 
 int DL_TOGGLE_MASK ; 
 scalar_t__ EMPTY_SCB ; 
 struct asd_ascb* asd_tc_index_find (struct asd_seq_data*,int) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct asd_ascb*,struct done_list_struct*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void asd_dl_tasklet_handler(unsigned long data)
{
	struct asd_ha_struct *asd_ha = (struct asd_ha_struct *) data;
	struct asd_seq_data *seq = &asd_ha->seq;
	unsigned long flags;

	while (1) {
		struct done_list_struct *dl = &seq->dl[seq->dl_next];
		struct asd_ascb *ascb;

		if ((dl->toggle & DL_TOGGLE_MASK) != seq->dl_toggle)
			break;

		/* find the aSCB */
		spin_lock_irqsave(&seq->tc_index_lock, flags);
		ascb = asd_tc_index_find(seq, (int)le16_to_cpu(dl->index));
		spin_unlock_irqrestore(&seq->tc_index_lock, flags);
		if (unlikely(!ascb)) {
			ASD_DPRINTK("BUG:sequencer:dl:no ascb?!\n");
			goto next_1;
		} else if (ascb->scb->header.opcode == EMPTY_SCB) {
			goto out;
		} else if (!ascb->uldd_timer && !del_timer(&ascb->timer)) {
			goto next_1;
		}
		spin_lock_irqsave(&seq->pend_q_lock, flags);
		list_del_init(&ascb->list);
		seq->pending--;
		spin_unlock_irqrestore(&seq->pend_q_lock, flags);
	out:
		ascb->tasklet_complete(ascb, dl);

	next_1:
		seq->dl_next = (seq->dl_next + 1) & (ASD_DL_SIZE-1);
		if (!seq->dl_next)
			seq->dl_toggle ^= DL_TOGGLE_MASK;
	}
}