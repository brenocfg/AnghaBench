#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  rnf_complete; int /*<<< orphan*/  rnf_error; int /*<<< orphan*/  rnf_submit; struct mon_reader_text* r_data; struct mon_bus* m_bus; } ;
struct mon_reader_text {struct mon_reader_text* printf_buf; TYPE_1__ r; int /*<<< orphan*/ * e_slab; int /*<<< orphan*/  slab_name; int /*<<< orphan*/  printf_size; int /*<<< orphan*/  printf_lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  e_list; } ;
struct mon_event_text {int dummy; } ;
struct mon_bus {int dummy; } ;
struct inode {struct mon_bus* i_private; } ;
struct file {struct mon_reader_text* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRINTF_DFL ; 
 int /*<<< orphan*/  SLAB_NAME_SZ ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mon_reader_text*) ; 
 struct mon_reader_text* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmem_cache_create (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mon_reader_text* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mon_lock ; 
 int /*<<< orphan*/  mon_reader_add (struct mon_bus*,TYPE_1__*) ; 
 int /*<<< orphan*/  mon_text_complete ; 
 int /*<<< orphan*/  mon_text_ctor ; 
 int /*<<< orphan*/  mon_text_error ; 
 int /*<<< orphan*/  mon_text_submit ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mon_reader_text*) ; 

__attribute__((used)) static int mon_text_open(struct inode *inode, struct file *file)
{
	struct mon_bus *mbus;
	struct mon_reader_text *rp;
	int rc;

	mutex_lock(&mon_lock);
	mbus = inode->i_private;

	rp = kzalloc(sizeof(struct mon_reader_text), GFP_KERNEL);
	if (rp == NULL) {
		rc = -ENOMEM;
		goto err_alloc;
	}
	INIT_LIST_HEAD(&rp->e_list);
	init_waitqueue_head(&rp->wait);
	mutex_init(&rp->printf_lock);

	rp->printf_size = PRINTF_DFL;
	rp->printf_buf = kmalloc(rp->printf_size, GFP_KERNEL);
	if (rp->printf_buf == NULL) {
		rc = -ENOMEM;
		goto err_alloc_pr;
	}

	rp->r.m_bus = mbus;
	rp->r.r_data = rp;
	rp->r.rnf_submit = mon_text_submit;
	rp->r.rnf_error = mon_text_error;
	rp->r.rnf_complete = mon_text_complete;

	snprintf(rp->slab_name, SLAB_NAME_SZ, "mon_text_%p", rp);
	rp->e_slab = kmem_cache_create(rp->slab_name,
	    sizeof(struct mon_event_text), sizeof(long), 0,
	    mon_text_ctor);
	if (rp->e_slab == NULL) {
		rc = -ENOMEM;
		goto err_slab;
	}

	mon_reader_add(mbus, &rp->r);

	file->private_data = rp;
	mutex_unlock(&mon_lock);
	return 0;

// err_busy:
//	kmem_cache_destroy(rp->e_slab);
err_slab:
	kfree(rp->printf_buf);
err_alloc_pr:
	kfree(rp);
err_alloc:
	mutex_unlock(&mon_lock);
	return rc;
}