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
typedef  int /*<<< orphan*/  vb2_thread_fnc ;
struct vb2_threadio_data {int /*<<< orphan*/ * thread; void* priv; int /*<<< orphan*/  fnc; } ;
struct vb2_queue {struct vb2_threadio_data* threadio; int /*<<< orphan*/  is_output; int /*<<< orphan*/  fileio; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __vb2_cleanup_fileio (struct vb2_queue*) ; 
 int __vb2_init_fileio (struct vb2_queue*,int) ; 
 int /*<<< orphan*/  dprintk (int,char*,int) ; 
 int /*<<< orphan*/  kfree (struct vb2_threadio_data*) ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct vb2_queue*,char*,char const*) ; 
 struct vb2_threadio_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_busy (struct vb2_queue*) ; 
 int /*<<< orphan*/  vb2_thread ; 

int vb2_thread_start(struct vb2_queue *q, vb2_thread_fnc fnc, void *priv,
		     const char *thread_name)
{
	struct vb2_threadio_data *threadio;
	int ret = 0;

	if (q->threadio)
		return -EBUSY;
	if (vb2_is_busy(q))
		return -EBUSY;
	if (WARN_ON(q->fileio))
		return -EBUSY;

	threadio = kzalloc(sizeof(*threadio), GFP_KERNEL);
	if (threadio == NULL)
		return -ENOMEM;
	threadio->fnc = fnc;
	threadio->priv = priv;

	ret = __vb2_init_fileio(q, !q->is_output);
	dprintk(3, "file io: vb2_init_fileio result: %d\n", ret);
	if (ret)
		goto nomem;
	q->threadio = threadio;
	threadio->thread = kthread_run(vb2_thread, q, "vb2-%s", thread_name);
	if (IS_ERR(threadio->thread)) {
		ret = PTR_ERR(threadio->thread);
		threadio->thread = NULL;
		goto nothread;
	}
	return 0;

nothread:
	__vb2_cleanup_fileio(q);
nomem:
	kfree(threadio);
	return ret;
}