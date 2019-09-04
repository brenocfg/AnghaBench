#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* irqhook ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  semaphore; } ;
struct TYPE_6__ {int actidx; int endidx; int* seq; int idx; TYPE_1__ act; } ;
typedef  TYPE_2__ hp_sdc_transaction ;
struct TYPE_7__ {int wcurr; int rcurr; int im; int* r7; int wi; int rqty; int /*<<< orphan*/  lock; int /*<<< orphan*/  task; scalar_t__ ibf; TYPE_2__** tq; int /*<<< orphan*/  rtq_lock; int /*<<< orphan*/  rtime; scalar_t__ set_im; } ;

/* Variables and functions */
 int HP_SDC_ACT_CALLBACK ; 
 int HP_SDC_ACT_DATAIN ; 
 int HP_SDC_ACT_DATAOUT ; 
 int HP_SDC_ACT_DATAREG ; 
 int HP_SDC_ACT_DEALLOC ; 
 int HP_SDC_ACT_DURING ; 
 int HP_SDC_ACT_POSTCMD ; 
 int HP_SDC_ACT_PRECMD ; 
 int HP_SDC_ACT_SEMAPHORE ; 
 int HP_SDC_CMD_SET_D0 ; 
 int HP_SDC_CMD_SET_IM ; 
 int HP_SDC_QUEUE_LEN ; 
 TYPE_4__ hp_sdc ; 
 int /*<<< orphan*/  hp_sdc_data_out8 (int) ; 
 int /*<<< orphan*/  hp_sdc_status_in8 () ; 
 int /*<<< orphan*/  hp_sdc_status_out8 (int) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  read_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

unsigned long hp_sdc_put(void)
{
	hp_sdc_transaction *curr;
	uint8_t act;
	int idx, curridx;

	int limit = 0;

	write_lock(&hp_sdc.lock);

	/* If i8042 buffers are full, we cannot do anything that
	   requires output, so we skip to the administrativa. */
	if (hp_sdc.ibf) {
		hp_sdc_status_in8();
		if (hp_sdc.ibf)
			goto finish;
	}

 anew:
	/* See if we are in the middle of a sequence. */
	if (hp_sdc.wcurr < 0)
		hp_sdc.wcurr = 0;
	read_lock_irq(&hp_sdc.rtq_lock);
	if (hp_sdc.rcurr == hp_sdc.wcurr)
		hp_sdc.wcurr++;
	read_unlock_irq(&hp_sdc.rtq_lock);
	if (hp_sdc.wcurr >= HP_SDC_QUEUE_LEN)
		hp_sdc.wcurr = 0;
	curridx = hp_sdc.wcurr;

	if (hp_sdc.tq[curridx] != NULL)
		goto start;

	while (++curridx != hp_sdc.wcurr) {
		if (curridx >= HP_SDC_QUEUE_LEN) {
			curridx = -1; /* Wrap to top */
			continue;
		}
		read_lock_irq(&hp_sdc.rtq_lock);
		if (hp_sdc.rcurr == curridx) {
			read_unlock_irq(&hp_sdc.rtq_lock);
			continue;
		}
		read_unlock_irq(&hp_sdc.rtq_lock);
		if (hp_sdc.tq[curridx] != NULL)
			break; /* Found one. */
	}
	if (curridx == hp_sdc.wcurr) { /* There's nothing queued to do. */
		curridx = -1;
	}
	hp_sdc.wcurr = curridx;

 start:

	/* Check to see if the interrupt mask needs to be set. */
	if (hp_sdc.set_im) {
		hp_sdc_status_out8(hp_sdc.im | HP_SDC_CMD_SET_IM);
		hp_sdc.set_im = 0;
		goto finish;
	}

	if (hp_sdc.wcurr == -1)
		goto done;

	curr = hp_sdc.tq[curridx];
	idx = curr->actidx;

	if (curr->actidx >= curr->endidx) {
		hp_sdc.tq[curridx] = NULL;
		/* Interleave outbound data between the transactions. */
		hp_sdc.wcurr++;
		if (hp_sdc.wcurr >= HP_SDC_QUEUE_LEN)
			hp_sdc.wcurr = 0;
		goto finish;
	}

	act = curr->seq[idx];
	idx++;

	if (curr->idx >= curr->endidx) {
		if (act & HP_SDC_ACT_DEALLOC)
			kfree(curr);
		hp_sdc.tq[curridx] = NULL;
		/* Interleave outbound data between the transactions. */
		hp_sdc.wcurr++;
		if (hp_sdc.wcurr >= HP_SDC_QUEUE_LEN)
			hp_sdc.wcurr = 0;
		goto finish;
	}

	while (act & HP_SDC_ACT_PRECMD) {
		if (curr->idx != idx) {
			idx++;
			act &= ~HP_SDC_ACT_PRECMD;
			break;
		}
		hp_sdc_status_out8(curr->seq[idx]);
		curr->idx++;
		/* act finished? */
		if ((act & HP_SDC_ACT_DURING) == HP_SDC_ACT_PRECMD)
			goto actdone;
		/* skip quantity field if data-out sequence follows. */
		if (act & HP_SDC_ACT_DATAOUT)
			curr->idx++;
		goto finish;
	}
	if (act & HP_SDC_ACT_DATAOUT) {
		int qty;

		qty = curr->seq[idx];
		idx++;
		if (curr->idx - idx < qty) {
			hp_sdc_data_out8(curr->seq[curr->idx]);
			curr->idx++;
			/* act finished? */
			if (curr->idx - idx >= qty &&
			    (act & HP_SDC_ACT_DURING) == HP_SDC_ACT_DATAOUT)
				goto actdone;
			goto finish;
		}
		idx += qty;
		act &= ~HP_SDC_ACT_DATAOUT;
	} else
	    while (act & HP_SDC_ACT_DATAREG) {
		int mask;
		uint8_t w7[4];

		mask = curr->seq[idx];
		if (idx != curr->idx) {
			idx++;
			idx += !!(mask & 1);
			idx += !!(mask & 2);
			idx += !!(mask & 4);
			idx += !!(mask & 8);
			act &= ~HP_SDC_ACT_DATAREG;
			break;
		}

		w7[0] = (mask & 1) ? curr->seq[++idx] : hp_sdc.r7[0];
		w7[1] = (mask & 2) ? curr->seq[++idx] : hp_sdc.r7[1];
		w7[2] = (mask & 4) ? curr->seq[++idx] : hp_sdc.r7[2];
		w7[3] = (mask & 8) ? curr->seq[++idx] : hp_sdc.r7[3];

		if (hp_sdc.wi > 0x73 || hp_sdc.wi < 0x70 ||
		    w7[hp_sdc.wi - 0x70] == hp_sdc.r7[hp_sdc.wi - 0x70]) {
			int i = 0;

			/* Need to point the write index register */
			while (i < 4 && w7[i] == hp_sdc.r7[i])
				i++;

			if (i < 4) {
				hp_sdc_status_out8(HP_SDC_CMD_SET_D0 + i);
				hp_sdc.wi = 0x70 + i;
				goto finish;
			}

			idx++;
			if ((act & HP_SDC_ACT_DURING) == HP_SDC_ACT_DATAREG)
				goto actdone;

			curr->idx = idx;
			act &= ~HP_SDC_ACT_DATAREG;
			break;
		}

		hp_sdc_data_out8(w7[hp_sdc.wi - 0x70]);
		hp_sdc.r7[hp_sdc.wi - 0x70] = w7[hp_sdc.wi - 0x70];
		hp_sdc.wi++; /* write index register autoincrements */
		{
			int i = 0;

			while ((i < 4) && w7[i] == hp_sdc.r7[i])
				i++;
			if (i >= 4) {
				curr->idx = idx + 1;
				if ((act & HP_SDC_ACT_DURING) ==
				    HP_SDC_ACT_DATAREG)
					goto actdone;
			}
		}
		goto finish;
	}
	/* We don't go any further in the command if there is a pending read,
	   because we don't want interleaved results. */
	read_lock_irq(&hp_sdc.rtq_lock);
	if (hp_sdc.rcurr >= 0) {
		read_unlock_irq(&hp_sdc.rtq_lock);
		goto finish;
	}
	read_unlock_irq(&hp_sdc.rtq_lock);


	if (act & HP_SDC_ACT_POSTCMD) {
		uint8_t postcmd;

		/* curr->idx should == idx at this point. */
		postcmd = curr->seq[idx];
		curr->idx++;
		if (act & HP_SDC_ACT_DATAIN) {

			/* Start a new read */
			hp_sdc.rqty = curr->seq[curr->idx];
			hp_sdc.rtime = ktime_get();
			curr->idx++;
			/* Still need to lock here in case of spurious irq. */
			write_lock_irq(&hp_sdc.rtq_lock);
			hp_sdc.rcurr = curridx;
			write_unlock_irq(&hp_sdc.rtq_lock);
			hp_sdc_status_out8(postcmd);
			goto finish;
		}
		hp_sdc_status_out8(postcmd);
		goto actdone;
	}

 actdone:
	if (act & HP_SDC_ACT_SEMAPHORE)
		up(curr->act.semaphore);
	else if (act & HP_SDC_ACT_CALLBACK)
		curr->act.irqhook(0,NULL,0,0);

	if (curr->idx >= curr->endidx) { /* This transaction is over. */
		if (act & HP_SDC_ACT_DEALLOC)
			kfree(curr);
		hp_sdc.tq[curridx] = NULL;
	} else {
		curr->actidx = idx + 1;
		curr->idx = idx + 2;
	}
	/* Interleave outbound data between the transactions. */
	hp_sdc.wcurr++;
	if (hp_sdc.wcurr >= HP_SDC_QUEUE_LEN)
		hp_sdc.wcurr = 0;

 finish:
	/* If by some quirk IBF has cleared and our ISR has run to
	   see that that has happened, do it all again. */
	if (!hp_sdc.ibf && limit++ < 20)
		goto anew;

 done:
	if (hp_sdc.wcurr >= 0)
		tasklet_schedule(&hp_sdc.task);
	write_unlock(&hp_sdc.lock);

	return 0;
}