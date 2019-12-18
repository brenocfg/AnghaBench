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
struct nvm_rq {int /*<<< orphan*/ * private; int /*<<< orphan*/  end_io; } ;
struct nvm_dev {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* submit_io ) (struct nvm_dev*,struct nvm_rq*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvm_sync_end_io ; 
 int stub1 (struct nvm_dev*,struct nvm_rq*,void*) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wait_for_completion_io (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvm_submit_io_wait(struct nvm_dev *dev, struct nvm_rq *rqd,
			      void *buf)
{
	DECLARE_COMPLETION_ONSTACK(wait);
	int ret = 0;

	rqd->end_io = nvm_sync_end_io;
	rqd->private = &wait;

	ret = dev->ops->submit_io(dev, rqd, buf);
	if (ret)
		return ret;

	wait_for_completion_io(&wait);

	return 0;
}