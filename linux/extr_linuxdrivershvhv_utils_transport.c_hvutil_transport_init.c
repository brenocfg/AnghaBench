#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_6__ {scalar_t__ idx; scalar_t__ val; } ;
struct TYPE_5__ {char const* name; TYPE_1__* fops; int /*<<< orphan*/  minor; } ;
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/  open; int /*<<< orphan*/  poll; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  owner; } ;
struct hvutil_transport {int (* on_msg ) (void*,int) ;void (* on_reset ) () ;int /*<<< orphan*/  list; TYPE_3__ cn_id; TYPE_2__ mdev; int /*<<< orphan*/  release; int /*<<< orphan*/  lock; int /*<<< orphan*/  outmsg_q; TYPE_1__ fops; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MISC_DYNAMIC_MINOR ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ cn_add_callback (TYPE_3__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hvt_cn_callback ; 
 int /*<<< orphan*/  hvt_list ; 
 int /*<<< orphan*/  hvt_list_lock ; 
 int /*<<< orphan*/  hvt_op_open ; 
 int /*<<< orphan*/  hvt_op_poll ; 
 int /*<<< orphan*/  hvt_op_read ; 
 int /*<<< orphan*/  hvt_op_release ; 
 int /*<<< orphan*/  hvt_op_write ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hvutil_transport*) ; 
 struct hvutil_transport* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ misc_register (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct hvutil_transport *hvutil_transport_init(const char *name,
					       u32 cn_idx, u32 cn_val,
					       int (*on_msg)(void *, int),
					       void (*on_reset)(void))
{
	struct hvutil_transport *hvt;

	hvt = kzalloc(sizeof(*hvt), GFP_KERNEL);
	if (!hvt)
		return NULL;

	hvt->cn_id.idx = cn_idx;
	hvt->cn_id.val = cn_val;

	hvt->mdev.minor = MISC_DYNAMIC_MINOR;
	hvt->mdev.name = name;

	hvt->fops.owner = THIS_MODULE;
	hvt->fops.read = hvt_op_read;
	hvt->fops.write = hvt_op_write;
	hvt->fops.poll = hvt_op_poll;
	hvt->fops.open = hvt_op_open;
	hvt->fops.release = hvt_op_release;

	hvt->mdev.fops = &hvt->fops;

	init_waitqueue_head(&hvt->outmsg_q);
	mutex_init(&hvt->lock);
	init_completion(&hvt->release);

	spin_lock(&hvt_list_lock);
	list_add(&hvt->list, &hvt_list);
	spin_unlock(&hvt_list_lock);

	hvt->on_msg = on_msg;
	hvt->on_reset = on_reset;

	if (misc_register(&hvt->mdev))
		goto err_free_hvt;

	/* Use cn_id.idx/cn_id.val to determine if we need to setup netlink */
	if (hvt->cn_id.idx > 0 && hvt->cn_id.val > 0 &&
	    cn_add_callback(&hvt->cn_id, name, hvt_cn_callback))
		goto err_free_hvt;

	return hvt;

err_free_hvt:
	spin_lock(&hvt_list_lock);
	list_del(&hvt->list);
	spin_unlock(&hvt_list_lock);
	kfree(hvt);
	return NULL;
}