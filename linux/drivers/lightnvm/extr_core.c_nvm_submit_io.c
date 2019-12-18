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
struct nvm_tgt_dev {int /*<<< orphan*/  geo; struct nvm_dev* parent; } ;
struct nvm_rq {int /*<<< orphan*/  flags; struct nvm_tgt_dev* dev; } ;
struct nvm_dev {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* submit_io ) (struct nvm_dev*,struct nvm_rq*,void*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  nvm_rq_dev_to_tgt (struct nvm_tgt_dev*,struct nvm_rq*) ; 
 int /*<<< orphan*/  nvm_rq_tgt_to_dev (struct nvm_tgt_dev*,struct nvm_rq*) ; 
 int /*<<< orphan*/  nvm_set_flags (int /*<<< orphan*/ *,struct nvm_rq*) ; 
 int stub1 (struct nvm_dev*,struct nvm_rq*,void*) ; 

int nvm_submit_io(struct nvm_tgt_dev *tgt_dev, struct nvm_rq *rqd, void *buf)
{
	struct nvm_dev *dev = tgt_dev->parent;
	int ret;

	if (!dev->ops->submit_io)
		return -ENODEV;

	nvm_rq_tgt_to_dev(tgt_dev, rqd);

	rqd->dev = tgt_dev;
	rqd->flags = nvm_set_flags(&tgt_dev->geo, rqd);

	/* In case of error, fail with right address format */
	ret = dev->ops->submit_io(dev, rqd, buf);
	if (ret)
		nvm_rq_dev_to_tgt(tgt_dev, rqd);
	return ret;
}