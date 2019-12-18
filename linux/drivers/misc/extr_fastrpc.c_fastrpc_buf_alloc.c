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
typedef  int u64 ;
struct fastrpc_user {TYPE_1__* sctx; } ;
struct fastrpc_buf {int size; scalar_t__ phys; int /*<<< orphan*/  lock; int /*<<< orphan*/ * virt; struct device* dev; struct fastrpc_user* fl; int /*<<< orphan*/  attachments; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {scalar_t__ sid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fastrpc_buf*) ; 
 struct fastrpc_buf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fastrpc_buf_alloc(struct fastrpc_user *fl, struct device *dev,
			     u64 size, struct fastrpc_buf **obuf)
{
	struct fastrpc_buf *buf;

	buf = kzalloc(sizeof(*buf), GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	INIT_LIST_HEAD(&buf->attachments);
	mutex_init(&buf->lock);

	buf->fl = fl;
	buf->virt = NULL;
	buf->phys = 0;
	buf->size = size;
	buf->dev = dev;

	buf->virt = dma_alloc_coherent(dev, buf->size, (dma_addr_t *)&buf->phys,
				       GFP_KERNEL);
	if (!buf->virt) {
		mutex_destroy(&buf->lock);
		kfree(buf);
		return -ENOMEM;
	}

	if (fl->sctx && fl->sctx->sid)
		buf->phys += ((u64)fl->sctx->sid << 32);

	*obuf = buf;

	return 0;
}