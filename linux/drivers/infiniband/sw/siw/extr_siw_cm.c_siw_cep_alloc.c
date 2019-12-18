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
struct siw_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  cep_list; } ;
struct siw_cep {int enhanced_rdma_conn_est; int /*<<< orphan*/  devq; struct siw_device* sdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  waitq; int /*<<< orphan*/  state; int /*<<< orphan*/  ref; int /*<<< orphan*/  work_freelist; int /*<<< orphan*/  listenq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIW_EPSTATE_IDLE ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct siw_cep* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siw_dbg_cep (struct siw_cep*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct siw_cep *siw_cep_alloc(struct siw_device *sdev)
{
	struct siw_cep *cep = kzalloc(sizeof(*cep), GFP_KERNEL);
	unsigned long flags;

	if (!cep)
		return NULL;

	INIT_LIST_HEAD(&cep->listenq);
	INIT_LIST_HEAD(&cep->devq);
	INIT_LIST_HEAD(&cep->work_freelist);

	kref_init(&cep->ref);
	cep->state = SIW_EPSTATE_IDLE;
	init_waitqueue_head(&cep->waitq);
	spin_lock_init(&cep->lock);
	cep->sdev = sdev;
	cep->enhanced_rdma_conn_est = false;

	spin_lock_irqsave(&sdev->lock, flags);
	list_add_tail(&cep->devq, &sdev->cep_list);
	spin_unlock_irqrestore(&sdev->lock, flags);

	siw_dbg_cep(cep, "new endpoint\n");
	return cep;
}