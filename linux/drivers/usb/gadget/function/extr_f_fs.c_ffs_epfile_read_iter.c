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
struct kiocb {int /*<<< orphan*/  ki_filp; struct ffs_io_data* private; } ;
struct iov_iter {int dummy; } ;
struct ffs_io_data {int aio; int read; struct iov_iter data; struct ffs_io_data* to_free; int /*<<< orphan*/  mm; struct kiocb* kiocb; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  io_data ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIOCBQUEUED ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* current ; 
 struct ffs_io_data* dup_iter (struct iov_iter*,struct iov_iter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffs_aio_cancel ; 
 int /*<<< orphan*/  ffs_epfile_io (int /*<<< orphan*/ ,struct ffs_io_data*) ; 
 int /*<<< orphan*/  is_sync_kiocb (struct kiocb*) ; 
 int /*<<< orphan*/  kfree (struct ffs_io_data*) ; 
 int /*<<< orphan*/  kiocb_set_cancel_fn (struct kiocb*,int /*<<< orphan*/ ) ; 
 struct ffs_io_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ffs_io_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t ffs_epfile_read_iter(struct kiocb *kiocb, struct iov_iter *to)
{
	struct ffs_io_data io_data, *p = &io_data;
	ssize_t res;

	ENTER();

	if (!is_sync_kiocb(kiocb)) {
		p = kzalloc(sizeof(io_data), GFP_KERNEL);
		if (unlikely(!p))
			return -ENOMEM;
		p->aio = true;
	} else {
		memset(p, 0, sizeof(*p));
		p->aio = false;
	}

	p->read = true;
	p->kiocb = kiocb;
	if (p->aio) {
		p->to_free = dup_iter(&p->data, to, GFP_KERNEL);
		if (!p->to_free) {
			kfree(p);
			return -ENOMEM;
		}
	} else {
		p->data = *to;
		p->to_free = NULL;
	}
	p->mm = current->mm;

	kiocb->private = p;

	if (p->aio)
		kiocb_set_cancel_fn(kiocb, ffs_aio_cancel);

	res = ffs_epfile_io(kiocb->ki_filp, p);
	if (res == -EIOCBQUEUED)
		return res;

	if (p->aio) {
		kfree(p->to_free);
		kfree(p);
	} else {
		*to = p->data;
	}
	return res;
}