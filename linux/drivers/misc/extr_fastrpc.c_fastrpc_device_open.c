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
struct inode {int dummy; } ;
struct file {struct fastrpc_user* private_data; } ;
struct fastrpc_user {int /*<<< orphan*/  user; int /*<<< orphan*/  mutex; int /*<<< orphan*/  sctx; struct fastrpc_channel_ctx* cctx; int /*<<< orphan*/  tgid; int /*<<< orphan*/  maps; int /*<<< orphan*/  pending; int /*<<< orphan*/  lock; } ;
struct fastrpc_channel_ctx {int /*<<< orphan*/  lock; int /*<<< orphan*/  users; TYPE_1__* rpdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  tgid; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fastrpc_channel_ctx_get (struct fastrpc_channel_ctx*) ; 
 int /*<<< orphan*/  fastrpc_session_alloc (struct fastrpc_channel_ctx*) ; 
 int /*<<< orphan*/  kfree (struct fastrpc_user*) ; 
 struct fastrpc_user* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct fastrpc_channel_ctx* miscdev_to_cctx (struct fastrpc_user*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int fastrpc_device_open(struct inode *inode, struct file *filp)
{
	struct fastrpc_channel_ctx *cctx = miscdev_to_cctx(filp->private_data);
	struct fastrpc_user *fl = NULL;
	unsigned long flags;

	fl = kzalloc(sizeof(*fl), GFP_KERNEL);
	if (!fl)
		return -ENOMEM;

	/* Released in fastrpc_device_release() */
	fastrpc_channel_ctx_get(cctx);

	filp->private_data = fl;
	spin_lock_init(&fl->lock);
	mutex_init(&fl->mutex);
	INIT_LIST_HEAD(&fl->pending);
	INIT_LIST_HEAD(&fl->maps);
	INIT_LIST_HEAD(&fl->user);
	fl->tgid = current->tgid;
	fl->cctx = cctx;

	fl->sctx = fastrpc_session_alloc(cctx);
	if (!fl->sctx) {
		dev_err(&cctx->rpdev->dev, "No session available\n");
		mutex_destroy(&fl->mutex);
		kfree(fl);

		return -EBUSY;
	}

	spin_lock_irqsave(&cctx->lock, flags);
	list_add_tail(&fl->user, &cctx->users);
	spin_unlock_irqrestore(&cctx->lock, flags);

	return 0;
}