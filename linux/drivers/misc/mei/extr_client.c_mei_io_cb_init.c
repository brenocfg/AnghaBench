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
struct mei_cl_cb {int fop_type; scalar_t__ buf_idx; struct mei_cl* cl; struct file const* fp; int /*<<< orphan*/  list; } ;
struct mei_cl {int dummy; } ;
struct file {int dummy; } ;
typedef  enum mei_cb_file_ops { ____Placeholder_mei_cb_file_ops } mei_cb_file_ops ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct mei_cl_cb* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mei_cl_cb *mei_io_cb_init(struct mei_cl *cl,
					enum mei_cb_file_ops type,
					const struct file *fp)
{
	struct mei_cl_cb *cb;

	cb = kzalloc(sizeof(struct mei_cl_cb), GFP_KERNEL);
	if (!cb)
		return NULL;

	INIT_LIST_HEAD(&cb->list);
	cb->fp = fp;
	cb->cl = cl;
	cb->buf_idx = 0;
	cb->fop_type = type;
	return cb;
}