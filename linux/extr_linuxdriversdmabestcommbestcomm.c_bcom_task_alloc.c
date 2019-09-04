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
struct bcom_task {int tasknum; int num_bd; int bd_size; struct bcom_task* cookie; int /*<<< orphan*/  bd; scalar_t__ irq; int /*<<< orphan*/  bd_pa; void* priv; } ;
struct TYPE_4__ {TYPE_1__* tdt; int /*<<< orphan*/  ofnode; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int stop; } ;

/* Variables and functions */
 int BCOM_MAX_TASKS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__* bcom_eng ; 
 int /*<<< orphan*/  bcom_sram_alloc (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcom_sram_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (scalar_t__) ; 
 scalar_t__ irq_of_parse_and_map (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct bcom_task*) ; 
 struct bcom_task* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 struct bcom_task* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct bcom_task *
bcom_task_alloc(int bd_count, int bd_size, int priv_size)
{
	int i, tasknum = -1;
	struct bcom_task *tsk;

	/* Don't try to do anything if bestcomm init failed */
	if (!bcom_eng)
		return NULL;

	/* Get and reserve a task num */
	spin_lock(&bcom_eng->lock);

	for (i=0; i<BCOM_MAX_TASKS; i++)
		if (!bcom_eng->tdt[i].stop) {	/* we use stop as a marker */
			bcom_eng->tdt[i].stop = 0xfffffffful; /* dummy addr */
			tasknum = i;
			break;
		}

	spin_unlock(&bcom_eng->lock);

	if (tasknum < 0)
		return NULL;

	/* Allocate our structure */
	tsk = kzalloc(sizeof(struct bcom_task) + priv_size, GFP_KERNEL);
	if (!tsk)
		goto error;

	tsk->tasknum = tasknum;
	if (priv_size)
		tsk->priv = (void*)tsk + sizeof(struct bcom_task);

	/* Get IRQ of that task */
	tsk->irq = irq_of_parse_and_map(bcom_eng->ofnode, tsk->tasknum);
	if (!tsk->irq)
		goto error;

	/* Init the BDs, if needed */
	if (bd_count) {
		tsk->cookie = kmalloc_array(bd_count, sizeof(void *),
					    GFP_KERNEL);
		if (!tsk->cookie)
			goto error;

		tsk->bd = bcom_sram_alloc(bd_count * bd_size, 4, &tsk->bd_pa);
		if (!tsk->bd)
			goto error;
		memset(tsk->bd, 0x00, bd_count * bd_size);

		tsk->num_bd = bd_count;
		tsk->bd_size = bd_size;
	}

	return tsk;

error:
	if (tsk) {
		if (tsk->irq)
			irq_dispose_mapping(tsk->irq);
		bcom_sram_free(tsk->bd);
		kfree(tsk->cookie);
		kfree(tsk);
	}

	bcom_eng->tdt[tasknum].stop = 0;

	return NULL;
}